**How to run the code**

**Source code files:**
benchmark.cpp
setUpArray.cpp 
mergeSort.cpp 
mergeSort_openMP.cpp
quickSort.cpp 
quickSort_openMP.cpp


_command for compiling the files when running Mergesort:_
g++ -fopenmp -o programm benchmark.cpp setUpArray.cpp mergeSort.cpp mergeSort_openMP.cpp


_command for compiling the files when running Quicksort:_
g++ -fopenmp -o programm benchmark.cpp setUpArray.cpp quickSort.cpp quickSort_openMP.cpp


**running the programm:**
./programm



_concurrency level has to be set as a command line argument. If concurrency level is not set, the code uses concurrency level 1._
./programm <concurrency level>

