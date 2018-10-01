from random import randint
import argparse
import collections

ElementRange = collections.namedtuple("ElementRange", ['min', 'max'])
cy_salary = ElementRange(20000, 150000)
ly_salary = ElementRange(18000, 130000)
cy_bonus = ElementRange(400, 15000)
ly_bonus = ElementRange(350, 13000)
cy_lunches = ElementRange(4, 52)
ly_lunches = ElementRange(5, 52)

class record(object):
    def __init__(self, companyId, employeeId):
        self.company = companyId
        self.employee = employeeId
        self.salary_previous = randint(ly_salary.min, ly_salary.max)
        self.salary_current = randint(self.salary_previous, cy_salary.max) # careful
        self.bonus_previous = randint(ly_bonus.min, ly_bonus.max)
        self.bonus_current = randint(cy_bonus.min, cy_bonus.max)
        self.lunches_previous = randint(ly_lunches.min, ly_lunches.max)
        self.lunches_current = randint(cy_lunches.min, cy_lunches.max)

    def set(self, comp,emp,sc,sp,bc,bp,lc,lp):
        self.company = comp
        self.employee = emp
        self.salary_current = sc
        self.salary_previous = sp
        self.bonus_current = bc
        self.bonus_previous = bp
        self.lunches_current = lc
        self.lunches_previous = lp

def GenRandList(min, max, count):
    randNums = []
    for x in range(1,count):
        randNums.append(randint(min, max))
    return randNums
    
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-r","--records", default=50, help="records per company",
                    type=int)
    parser.add_argument("-c","--companies", default=25,  help="companies to generate",
                    type=int)
    parser.add_argument("-o","--output", default="comp_records.txt", help="output file name",
                    type=str)
    parser.add_argument("-v","--verbose", action='store_true', help="print records after creation")

    args=vars(parser.parse_args())
    output_filename = args["output"]
    verbose = args["verbose"]
    records_per_company = args["records"]
    num_companies = args["companies"]
    companyIds = range(0, num_companies)
    data_records=[]

    for c in companyIds:
        for e in range(0,records_per_company):
            rec = record(c, e)
            data_records.append(rec)
    
    print "Intialised " + str(records_per_company) +" records for " + str(num_companies) + " companies"

    if verbose is True:
        for r in data_records:  
            attrs = vars(r) 
            print ', '.join("%s: %s" % item for item in attrs.items())

    output_file = open(output_filename, "w")

    for r in data_records:
        #ugly but we can't preserve declaraation order :()
        print >> output_file, ','.join(str(x) for x in [r.company,r.employee,r.salary_previous,r.salary_current,r.bonus_previous,r.bonus_current,r.lunches_previous,r.lunches_current])

    print "Created " + output_filename + " (" + str(records_per_company * num_companies) + " records)" 

if __name__ == "__main__":
    main()
