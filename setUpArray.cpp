#include <iostream>
#include <random>
/*------- This method sets up the arrays with different proble sizes N -------*/



void setup(int64_t N, uint64_t* A){
    srand48(2);  // 2 is seed value

    for(int64_t i = 0; i < N; ++i) {
        A[i] = lrand48() % N; // random values between 0 and N-1
    }
}
