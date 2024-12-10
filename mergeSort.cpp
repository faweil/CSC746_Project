#include <iostream>
#include <cstring>
/*------- This is the serial merge sort implementation -------*/

// Array = array which has to get sorted in ascending order


void merge(uint64_t* Array, int64_t n, uint64_t* tmp) {
   int64_t i = 0;
   int64_t j = n/2;
   int64_t k = 0;

   while (i<n/2 && j<n) {
      if (Array[i] < Array[j]) {
         tmp[k] = Array[i];
         k++; 
         i++;
      } else {
         tmp[k] = Array[j];
         k++; 
         j++;
      }
   }
   while (i<n/2) { // lower half
      tmp[k] = Array[i];
      k++; 
      i++;
   }
      while (j<n) { // upper half
         tmp[k] = Array[j];
         k++; 
         j++;
   }
   memcpy(Array, tmp, n*sizeof(uint64_t));

}



// Divides the array in sub arrays and calls the merge function if it can not divide sub array anymore
void mergeSort(uint64_t* Array, int64_t n, uint64_t* tmp)
{
   if (n < 2) return;

   mergeSort(Array, n/2, tmp);                  // left array

   mergeSort(Array+(n/2), n-(n/2), tmp+(n/2));  // right array

   merge(Array, n, tmp);                        // merge two sub arrays back together
}

