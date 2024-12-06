#include <iostream>
#include <cstring>
#include <omp.h>

/*------- This is the parallel merge sort implementation with openMP-------*/

// Array = array which has to get sorted in ascending order
// lb = lower bound, first index of Array
// ub = upper bound, last index of Array
// mid = mid of array

extern void mergeSort(uint64_t* A, int64_t n, uint64_t* t);


void merge_openMP(uint64_t* Array, int64_t n, uint64_t* tmp) {
   int64_t i = 0;
   int64_t j = n/2;
   int64_t ti = 0;

   while (i<n/2 && j<n) {
      if (Array[i] < Array[j]) {
         tmp[ti] = Array[i];
         ti++; i++;
      } else {
         tmp[ti] = Array[j];
         ti++; j++;
      }
   }
   while (i<n/2) { /* finish up lower half */
      tmp[ti] = Array[i];
      ti++; i++;
   }
      while (j<n) { /* finish up upper half */
         tmp[ti] = Array[j];
         ti++; j++;
   }
   memcpy(Array, tmp, n*sizeof(uint64_t));

}


// Divides the array in sub arrays and calls the merge function if it can not divide sub array anymore
void mergeSort_parallel(uint64_t* Array, int64_t n, uint64_t* tmp, int64_t taskLimit){

   if (n < 2) return;


    if (n < taskLimit ){
        //small array, therefore sort sequential
        //std::cout << "going to sequential sorting" << std::endl;
        return mergeSort(Array, n, tmp);

    }else{
        //std::cout << "Parallel sorting" << std::endl;

        #pragma omp task shared(Array)
        mergeSort_parallel(Array, n/2, tmp, taskLimit);             // left array
        #pragma omp task shared(Array)
        mergeSort_parallel(Array+(n/2), n-(n/2), tmp, taskLimit);         // right array

        #pragma omp taskwait
        merge_openMP(Array, n, tmp);             // merge two sub arrays back together
    }
}



void mergeSort_openMP(uint64_t* Array, int64_t n, uint64_t* tmp){
    #pragma omp parallel
        {
            #pragma omp single
            mergeSort_parallel(Array, n, tmp, 300);
        }

}


