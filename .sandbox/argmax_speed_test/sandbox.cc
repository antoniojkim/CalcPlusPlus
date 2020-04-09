#include <iostream>
#include <cstdlib>
#include <ctime>

#include <gsl/gsl_statistics.h>

using namespace std;

template<typename T>
size_t argmax(const T* array, size_t stride, size_t size){
    const T* max = array;
    const T* end = array+size;
    for(const T* a = array+1; a < end; a += stride){
        if (*a > *max){
            max = a;
        }
    }
    return (size_t)(max - array);
}

typedef size_t (*func_t)(const double*, size_t, size_t);

void timeit(func_t f, const double* a, size_t stride, size_t N){
    std::clock_t start = std::clock();

    unsigned long long isum = 0;
    for (int i = 0; i<100000; ++i){
        isum += f(a, stride, N);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const std::size_t N = 100000;
    double a[N];
    for (std::size_t i = 0; i < N; ++i){
        a[i] = (double) rand();
    }

    timeit(argmax, a, 1, N);  // 4.86935 seconds
    timeit(gsl_stats_max_index, a, 1, N);  // 9.24717 seconds
}

