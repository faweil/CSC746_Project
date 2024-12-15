#include <iostream>
#include <omp.h>
/*------- This is the parallel quick sort implementation with openMP-----------*/
// Array = array which has to get sorted in ascending order
// lb = lower bound, first index of Array
// ub = upper bound, last index of Array
// pivot = last element in the Array
extern void quickSort(int64_t lb, int64_t ub, uint64_t* A);



int partition_openMP(int64_t lb, int64_t ub, uint64_t* Array){
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


void quickSort_parallel(int64_t lb, int64_t ub, uint64_t* Array, int64_t taskLimit){

    if(lb < ub)
    {
        if ((ub - lb) < taskLimit ){
            //small array, therefore sort sequential
            return quickSort(lb, ub, Array);

        }else{
            int64_t pivot_index = partition_openMP(lb, ub, Array);

            #pragma omp task shared(Array)
                quickSort_parallel(lb, pivot_index - 1, Array, taskLimit);            // left part of array
            #pragma omp task shared(Array)
                quickSort_parallel(pivot_index + 1, ub, Array, taskLimit);            // right part of array
        }
    }
}

void quickSort_openMP(int64_t lb, int64_t ub, uint64_t* Array){
    #pragma omp parallel
        {
            #pragma omp single
            quickSort_parallel(lb, ub, Array, 300);
            #pragma omp taskwait
        }
}
