#include <iostream>
#include <cstring>
/*------- This is the serial merge sort implementation -------*/

// Array = array which has to get sorted in ascending order
// lb = lower bound, first index of Array
// ub = upper bound, last index of Array
// mid = mid of array


/* void merge(int64_t lb, int64_t mid, int64_t ub, uint64_t* Array){
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
} */

void merge(uint64_t* Array, int64_t n, uint64_t* tmp) {
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

} // end of merge()




void mergeSort(uint64_t* Array, int64_t n, uint64_t* tmp)
{
   if (n < 2) return;

   mergeSort(Array, n/2, tmp);

   mergeSort(Array+(n/2), n-(n/2), tmp);

    /* merge sorted halves into sorted list */
   merge(Array, n, tmp);
}


// Divides the array in sub arrays and calls the merge function if it can not divide sub array anymore
/* void mergeSort(int64_t lb, int64_t ub, uint64_t* Array){

    if(lb < ub){
        int64_t mid = lb + (ub - lb) / 2;
        mergeSort(lb, mid, Array);             // left array
        mergeSort(mid + 1, ub, Array);         // right array
        merge(lb, mid, ub, Array);             // merge two sub arrays back together
    }
} */








