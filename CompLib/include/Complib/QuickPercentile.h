#pragma once
#include <cstddef>
#include <array>
#include <cmath>

#include "CompDefs.h"


template<typename T>
class QuickPercentile
{
private:

	T data;
	size_t length;
	index_t last_pivot;

public:

	template<typename T>
	QuickPercentile(T new_data, size_t count)
	{
		data = new_data;
		length = count;
	}

	template<typename T>
	T GetRecord(index_t b)
	{
		return data[b];
	}

	double SelectPercentile(double percentile)   //convert a percentile 0.0 to 1.0 to the kth element
	{
		if (percentile < 0.0 || percentile > 100.0)   //invalid percentile
			return -1.0;

		percentile = percentile / 100.0;
		//if (percentile == 1.0)  //max. element for 100th percentile
		//	return std::max(data);

		//if (percentile == 0.0)  //min. element for 0th percentile
		//	return std::min(data);

		double lowerIndexContinuous = percentile * static_cast<double>(length - 1);     //get percentile location across continuous range
		index_t setIndex = static_cast<int>(std::floor(lowerIndexContinuous));               //get the lowest integer element this can be
		double interpolateFactor = lowerIndexContinuous - static_cast<double>(setIndex);        //work out interpolation factor for element above

		double percentileResult = data[SelectElement(setIndex + 1)] * (1.0 - interpolateFactor);

		if (interpolateFactor > 0.0 && (setIndex + 1 + 1) < length)
		{
			percentileResult = percentileResult + (interpolateFactor * data[NextHighestElement(last_pivot)]); // scan to right of last pivot value for next highest element
		}

		return percentileResult;        //SelectElement(oldelementindex);
	}

private:

	index_t NextHighestElement(index_t final_pivot)
	{
		//type deduction
		auto smallest = data[final_pivot + 1];
		index_t index_of_smallest = final_pivot + 1;

		for (index_t i = final_pivot + 1; i < length; i++)
			if (data[i] < smallest)
			{
				smallest = data[i];
				index_of_smallest = i;
			}
		return index_of_smallest;
	}

	// TODO: alter to return index f element within data
	index_t SelectElement(index_t k)  //indexes from 1
	{
		if (length == 1) //if only one element, return it
			return data[0];

		if (k > length - 1)  //if greater than number of elements, return highest element
			k = length - 1;

		index_t left = 0;                   //initial list bounds
		index_t right = length - 1;

		while (true)    //repeatedly partition until we pivot on the kth element
		{
			index_t newPivot = PartitionList(left, right);  //get a new element to pivot on
			index_t pivotDistance = newPivot - left + 1;    //get distance of the pivot

			if (pivotDistance == k) //if we pivoted on the desired kth number, return element k
			{
				last_pivot = newPivot;
				return newPivot;
			}
			else if (k < pivotDistance) //if we pivoted above that number
			{
				right = newPivot - 1;   //set the rightmost part of the list under the pivot
			}
			else // (k > pivotDistance) // else we pivoted below the number
			{
				k = k - pivotDistance;  //adjust the index we're after for the sublist
				left = newPivot + 1;    //so set leftmost part of the list above pivot
			}
		}

	}

	index_t PartitionList(index_t left, index_t right)  //partition the list based on a random pivot element
	{
		index_t pivotIndex = MedianOfThreePivot(left, right); 
		index_t storeIndex = left;
		auto pivotValue = data[pivotIndex];
		std::swap(data[pivotIndex], data[right]);
		
		for (index_t i = left; i < right; i++)   //from first to last but one element (last now contains pivot)
		{
			if (data[i] < pivotValue)        //if less than pivot value, place to left
			{
				std::swap(data[i], data[storeIndex]);
				storeIndex++;
			}
		}

		std::swap(data[storeIndex], data[right]);   //place pivot value in list[storeindex]

		return storeIndex;  //return index of pivot in newly partitioned list
	}

	index_t MedianOfThreePivot(index_t left, index_t right) //should avoid natural pathological cases for pivot
	{
		index_t mid = (left + right) / 2;

		if (data[right] < data[left])
			std::swap(data[left], data[right]);

		if (data[mid] < data[left])
			std::swap(data[mid], data[left]);

		if (data[right] < data[mid])
			std::swap(data[right], data[mid]);
		
		return mid;
	}
};