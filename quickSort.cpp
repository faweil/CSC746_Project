#include <iostream>
/*------- This is the serial quick sort implementation -------*/

// Array = array which has to get sorted in ascending order
// lb = lower bound, first index of Array
// ub = upper bound, last index of Array
// pivot = last element in the Array

int partition(int64_t lb, int64_t ub, uint64_t* Array){
    int64_t pivot = Array[ub];
    int64_t i = lb - 1;
    

    for(int64_t j = lb; j < ub; ++j){
        if(Array[j] < pivot){
	        //swap arr[i+1] and arr[j
            i++;
	        int64_t help = Array[i];
            Array[i] = Array[j];
            Array[j] = help;
	    }
    }

    //swap arr[i+1] and arr[ub] (pivot)
    i++;
    Array[ub] = Array[i];
    Array[i] = pivot;
    return i;
}


void quickSort(int64_t lb, int64_t ub, uint64_t* Array){

    if(lb < ub){
        int64_t pivot_index = partition(lb, ub, Array);
        quickSort(lb, pivot_index - 1, Array);            // left part of array
        quickSort(pivot_index + 1, ub, Array);            // right part of array
    }

}
