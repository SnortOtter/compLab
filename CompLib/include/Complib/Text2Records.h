#pragma once
#include "CompDefs.h"
#include "libDefs/Error.h"
#include <sstream>

class Text2Records {

	std::vector<compRecord_t> parsed_records;
	std::stringstream string_buffer;

public:
	
	int32_t ReadFile(std::string path);
	int32_t ParseToRecords();
	compRecord_t* GetRecords() { return parsed_records.data(); }
	size_t NumRecords() { return parsed_records.size();  }
	
};