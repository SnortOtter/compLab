// CompDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "Complib/QuickPercentile.h"
#include "Complib/Database.h"
#include "Complib/Text2Records.h"


int main(int argc, char *argv[])
{
	Text2Records recordParser;
	std::string raw_path = R"(C:\Users\Chris\Documents\git\CompLib\CompDemo\comp_records.txt)";
	recordParser.ReadFile(raw_path);
	recordParser.ParseToRecords();
	Database<compRecord_t> data;
	
	compRecord_t* records = recordParser.GetRecords();
	size_t num_records = recordParser.NumRecords();
	for (size_t i = 0; i < num_records; i++)
		data.Insert(records[i]);

	std::vector<compElement_t> selected = data.Select(&compRecord_t::salary_current);

	QuickPercentile<compElement_t*> mclagans(selected.data(), num_records);

	std::cout << "ni\n";

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
