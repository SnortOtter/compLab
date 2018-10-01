using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuickSelectResearch
{
    
    //Partitions list until pivoting on kth element


    class QuickSelector
    {
        private List<double> _values;           //elements to get percentile from
        private double lowerIndexContinuous;    //the percentile of the total number of elements
        private int _lastPivot;                 //if we need to interpolate, we can get the next highest element with a linear scan. Record pivot for lower element
        private double interpolateFactor;               //the factor with which to interpolate to the upper element

        public  QuickSelector(List<double> data)    //pass list with constructor
        {
            _values = data;
        }

        public void NewList(List<double> data)      //set a new list
        {
            _values = data;
        }

        public double? SelectPercentile(double percentile)   //convert a percentile 0.0 to 1.0 to the kth element
        {
            if (percentile < 0.0 || percentile > 1.0)   //invalid percentile
                return null;

            if (percentile == 1.0)  //max. element for 100th percentile
                return _values.Count;

            if (percentile == 0.0)  //min. element for 0th percentile
                return 1;

            lowerIndexContinuous = percentile * (double)(_values.Count - 1);     //get percentile location across continuous range
            int setIndex = (int)Math.Floor(lowerIndexContinuous);               //get the lowest integer element this can be
            interpolateFactor = lowerIndexContinuous -(double) setIndex;        //work out interpolation factor for element above

            double percentileResult =  SelectElement(setIndex+1) * (1.0 - interpolateFactor);

            if (interpolateFactor > 0.0 && (setIndex + 1 + 1) < _values.Count)
            {
                percentileResult = percentileResult + (interpolateFactor * NextHighestElement(_lastPivot)); // scan to right of last pivot value for next highest element
            }

            return percentileResult;        //SelectElement(oldelementindex);
        }

        private double NextHighestElement(int finalPivot)
        {
            double smallest = _values[finalPivot + 1];

            for (int i = finalPivot + 1 ; i < _values.Count; i++)
                if (_values[i] < smallest)
                    smallest = _values[i];
            return smallest;
        }

        public double SelectElement(int k)  //indexes from 1
        {
            if (_values.Count == 1) //if only one element, return it
                return _values[0];

            if (k > _values.Count - 1)  //if greater than number of elements, return highest element
                k = _values.Count - 1;

            int left = 0;                   //initial list bounds
            int right = _values.Count-1;

            while (true)    //repeatedly partition until we pivot on the kth element
            {
                int newPivot = PartitionList(left, right);  //get a new element to pivot on
                int pivotDistance = newPivot - left + 1;    //get distance of the pivot

                if (pivotDistance == k) //if we pivoted on the desired kth number, return element k
                {
                    _lastPivot = newPivot;
                    return _values[newPivot];
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

        public int PartitionList(int left, int right)  //partition the list based on a random pivot element
        {
            int pivotIndex = MedianOfThreePivot(left, right);   //
            int storeIndex = left;
            double pivotValue = _values[pivotIndex];

            _values[pivotIndex] = _values[right];            //swap last element and pivot element
            _values[right] = pivotValue;

            for (int i = left; i < right; i++)   //from first to last but one element (last now contains pivot)
            {
                if (_values[i] < pivotValue)        //if less than pivot value, place to left
                {
                    Swap(_values, i, storeIndex);
                    storeIndex++;
                }
            }

            Swap(_values, storeIndex, right);   //place pivot value in list[storeindex]

            return storeIndex;  //return index of pivot in newly partitioned list
        }

        private int MedianOfThreePivot(int left, int right) //should avoid natural pathological cases for pivot
        {
            int mid = (left+right) / 2;

            if (_values[right] < _values[left])
                Swap(_values, left, right);        

            if (_values[mid] < _values[left])
                Swap(_values, mid, left);

            if (_values[right] < _values[mid])
                Swap(_values, right, mid);

            return mid;
        }

        
        private void Swap(List<double> list, int indexA, int indexB)    //swap list elements
        {
            double tmp = list[indexA];
            list[indexA] = list[indexB];
            list[indexB] = tmp;
        }


    }
}
