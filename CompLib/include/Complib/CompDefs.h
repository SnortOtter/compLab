#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

using index_t = std::size_t;
using compElement_t = uint32_t;
using companyId_t = unsigned char[8];
using employeeId_t = unsigned char[16];

struct compRecord_t {
	uint32_t company_id;
	uint32_t employee_id;
	compElement_t salary_current;
	compElement_t salary_previous;
	compElement_t bonus_current;
	compElement_t bonus_previous;
	compElement_t lunches_current;
	compElement_t lunches_previous;
};

using  compDb_t = std::vector<compRecord_t>;

// function type for computing derived comp elements (abuse of std::function)
using f_CompDynamicElement = std::function<compElement_t(compRecord_t)>;	