#include <iostream>
#include <cstring>
#include <omp.h>

/*------- This is the parallel merge sort implementation with openMP-------*/

// Array = array which has to get sorted in ascending order
// lb = lower bound, first index of Array
// ub = upper bound, last index of Array
// mid = mid of array


void merge_openMP(int64_t lb, int64_t mid, int64_t ub, uint64_t* Array){
    int64_t i = lb;                             // index from left sub array
    int64_t j = mid + 1;                        // index from right sub array
    int64_t k = lb;                             // index from help_array
    int64_t* help_array = new int64_t[ub + 1];  // help_array

    while(i <= mid && j <= ub){
        if(Array[i] <= Array[j]){
            help_array[k] = Array[i];
            ++i;
        }
        else {
            help_array[k] = Array[j];
            ++j;
        }
        ++k;
    }


    if(i > mid){
        while(j <= ub){
            help_array[k] = Array[j];
            ++j;
            ++k;
        }
    }else {
        while(i <= mid){
            help_array[k] = Array[i];
            ++i;
            ++k;
        }
    }

    memcpy(Array + lb, help_array + lb, (ub - lb + 1) * sizeof(int64_t)); // copy help_array into finale array

    delete[] help_array;
}


// Divides the array in sub arrays and calls the merge function if it can not divide sub array anymore
void mergeSort_parallel(int64_t lb, int64_t ub, uint64_t* Array, int64_t taskLimit){

    if(lb < ub){
        int64_t mid = lb + (ub - lb) / 2;

        #pragma omp task shared(Array)
            mergeSort_parallel(lb, mid, Array, taskLimit);             // left array
        #pragma omp task shared(Array)
            mergeSort_parallel(mid + 1, ub, Array, taskLimit);         // right array

        #pragma omp taskwait
        merge_openMP(lb, mid, ub, Array);             // merge two sub arrays back together
    }
}





void mergeSort_openMP(int64_t lb, int64_t ub, uint64_t* Array){
    #pragma omp parallel
        {
            #pragma omp single
            mergeSort_parallel(lb, ub, Array, 300);
        }

}


