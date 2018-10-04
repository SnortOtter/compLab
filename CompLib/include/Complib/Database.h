#pragma once

#include <memory>

#include "CompDefs.h"

template <typename R>
class Database {

private:
	std::unique_ptr<std::vector<R>> records;

public:

	// Constructor that copies an array
	template <typename R>
	Database(R *record_array, std::size_t length)
	{
		InsertAll(record_array, length);
	}

	// constructor that takes ownership of a vector
	template <typename R>
	Database(std::unique_ptr<std::vector<R>> vec)
	{
		records = std::move(vec);
	}

	void Drop()
	{
		records.clear();
	}

	template <typename R>
	size_t Insert(R new_record)
	{
		records.push_back(new_record);
		return records.size();
	}

	template <typename R>
	void InsertAll(R *record_set, std::size_t length)
	{
		records.insert(records.end(), record_set, record_set[length]);
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
	std::vector<T> SelectWhere(T (R::*field), std::function<bool(compRecord_t)> f_where) const
	{
		std::vector<T> selected;
		std::vector<R> *data = records.get();

		for (auto& rec : *data) {
			if (f_where(rec))
				selected.push_back(rec.*field);
		}

		return selected;
	}

	template <typename T>
	std::vector<T> Select(T R::* field) const 
	{
		std::vector<T> selected;
		std::vector<R> *data = records.get();

		for (auto& rec : *data)
			selected.push_back(rec.*field);

		return selected;
	}

	std::size_t Count()
	{
		return records->size();
	}

};


