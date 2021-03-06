// CompDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


#include "Complib/QuickPercentile.h"
#include "Complib/Database.h"
#include "Complib/Text2Records.h"


int main(int argc, char *argv[])
{
	std::cout << "\n### C++ comp processing demo ###\n";

	// get demo data from csv
	Text2Records recordParser;
	std::string raw_path = R"(C:\Users\Chris\Documents\git\CompLib\CompDemo\comp_records.db)";
	recordParser.ReadFile(raw_path);
	recordParser.ParseToRecords();
	std::cout << "Parsed " << recordParser.NumRecords()  << " records from file: " << recordParser.SourceFile() << "\n";
	
	// silly database example 
	Database<compRecord_t> comp_db(recordParser.GetRecords());
	std::cout << "Moved " << comp_db.Count() << " records to the database.\n";

	// Select a column
	std::vector<compElement_t> selected = comp_db.Select(&compRecord_t::salary_current);

	// Init. a persistent qp instance 
	QuickPercentile<compElement_t*> mclagans(selected.data(), selected.size());

	double p50 = mclagans.SelectPercentile(50.0);

	std::cout << "50th percentile was: " << std::to_string(p50) << "\n";


}
