#include "stdafx.h"
#include "Complib/Text2Records.h"

#include <streambuf>
#include <fstream>

#include "libDefs/Error.h"

int32_t Text2Records::ReadFile(std::string path)
{
	std::ifstream t(path);

	if (!t.good())
		return Error::E_ERROR;

	string_buffer << t.rdbuf();

	if (0 == string_buffer.rdbuf()->in_avail())
		return Error::E_ERROR;

	return Error::S_OK;
}

// assume each line as a record
// each data element is comma separated

int32_t Text2Records::ParseToRecords()
{
	if (0 == string_buffer.rdbuf()->in_avail())
		return Error::E_ERROR;

	parsed_records.clear();

	std::string line_text;

	while (std::getline(string_buffer, line_text, '\n')) {
		
		std::stringstream line_text_stream(line_text);
		std::vector<std::string> line_elements(8);
		std::string s;

		while (std::getline(line_text_stream, s, ','))
		{
			line_elements.push_back(s);
		}

		if (line_elements.size() != 8)
			continue;

		compRecord_t rec;
		rec.company_id = std::stoul(line_elements[0], nullptr, 10);
		rec.employee_id = std::stoul(line_elements[1], nullptr, 10);
		rec.salary_current = std::stoul(line_elements[2], nullptr, 10);
		rec.salary_previous = std::stoul(line_elements[3], nullptr, 10);
		rec.bonus_current = std::stoul(line_elements[4], nullptr, 10);
		rec.bonus_previous = std::stoul(line_elements[5], nullptr, 10);
		rec.lunches_current = std::stoul(line_elements[6], nullptr, 10);
		rec.lunches_previous = std::stoul(line_elements[7], nullptr, 10);
	}

	return Error::S_OK;
}
