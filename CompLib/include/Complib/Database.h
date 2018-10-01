#pragma once

#include "CompDefs.h"

template <typename R>
class Database {

	std::vector<R> records;

public:

	template <typename R>
	size_t Insert(R new_record)
	{
		records.push_back(new_record);
		return records.size();
	}

	template <typename R>
	bool Reserve(size_t newSize)
	{
		if (newSize <= records.size())
			return false;

		records.reserve(newSize);
		return true;
	}

	template <typename T>
	std::vector<T> SelectWhere(T (R::*field), std::function<bool(compRecord_t)> f_where)
	{
		std::vector<T> data;

		for (auto&& rec : records) {
			if (f_where(rec))
				data.push_back(rec.*field);
		}

		return data;
	}

	template <typename T>
	std::vector<T> Select(T R::* field) const 
	{
		std::vector<T> data;

		for (auto&& rec : records)
			data.push_back(rec.*field);

		return data;
	}

};


