// CompDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

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

	for (auto &elem : selected)
		std::cout << elem << '\n'  ;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
