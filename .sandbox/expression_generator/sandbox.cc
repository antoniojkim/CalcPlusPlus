#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef size_t (*func_t)(float*, int);

void timeit(func_t f, float* a, int N){
    std::clock_t start = std::clock();

    size_t isum = 0;
    for (int i = 0; i<100000; ++i){
        isum += f(a, N);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const int N = 10000;
    float a[N];
    for (int i = 0; i < N; ++i){
        a[i] = (float) rand();
    }
}
