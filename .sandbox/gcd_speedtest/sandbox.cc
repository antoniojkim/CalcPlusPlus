#include <iostream>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <cmath>

using namespace std;

long long iterative_gcd(long long a, long long b){
    long long r;
    while (b != 0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

typedef long long (*func_t)(long long, long long);

void timeit(func_t f, double* a, double* b, size_t N){
    std::clock_t start = std::clock();

    long long gcds = 0;
    for (size_t j = 0; j < 100; ++j){
        for (size_t i = 0; i<N; ++i){
            if (std::trunc(a[i]) == a[i] && std::trunc(b[i]) == b[i]){
                gcds += f((long long) a[i], (long long) b[i]);
            }
        }
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "gcds: " << gcds << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const int N = 100000;
    double a[N];
    double b[N];
    for (int i = 0; i < N; ++i){
        a[i] = (double) rand();
        b[i] = (double) rand();
    }

    timeit(std::gcd<long long, long long>, a, b, N);
    timeit(iterative_gcd, a, b, N);
}
