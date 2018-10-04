#pragma once
#include "CompDefs.h"
#include "libDefs/Error.h"
#include <sstream>

class Text2Records {

	std::unique_ptr<std::vector<compRecord_t>> parsed_records;
	std::stringstream string_buffer;
	std::string path;

public:
	
	std::string SourceFile() const;
	int32_t ReadFile(std::string path);
	int32_t ParseToRecords();
	size_t NumRecords() { return parsed_records->size(); }

	// transfers ownership of the vector so we don't have to create a copy
	std::unique_ptr<std::vector<compRecord_t>> GetRecords() { return std::move(parsed_records); }
};