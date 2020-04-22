#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <numeric>

#include <gsl/gsl_math.h>

using namespace std;

bool gcd_method(double num, long& numerator, long& denominator){
    double precision = 1e8;

    double whole = std::floor(num);
    double fractional = (num - whole) * precision;

    long result = gcd((long) fractional, (long) precision);

    numerator = (long) (fractional / result);
    denominator = (long) (precision / result);

    return true;
}

bool binary_search_method(double num, long& numerator, long& denominator){
    double whole = std::floor(num);
    double fractional = num - whole;

    numerator = 1;
    denominator = 1;

    for (int i = 0; i < 100000; ++i){
        double approx = (double) numerator / denominator;
        switch(gsl_fcmp(fractional, approx, 1e-13)){
            case 0:
                // numerator += (long)(whole * denominator);
                return true;
            case -1:
                ++denominator;
                break;
            case 1:
                ++numerator;
                break;
            default:
                throw;
        }
    }

    return false;
}

bool algo_method(double num, long& numerator, long& denominator){
    double sign = num < 0 ? -1 : 1;
    double g = std::abs(num);
    long a = 0, b = 1, c = 1, d = 0;
    long s;
    int iter = 0;
    numerator = 0, denominator = 1;
    while (iter++ < 1e6){
        s = (long) std::floor(g);
        numerator = a + s*c;
        denominator = b + s*d;
        a = c;
        b = d;
        c = numerator;
        d = denominator;
        g = 1.0/(g-s);
        if(gsl_fcmp(sign*numerator/denominator, num, 1e-13) == 0){
            numerator *= sign;
            return true;
        }
    }
    return false;
}

typedef bool (*func_t)(double, long&, long&);

void timeit(func_t f, double a){
    std::clock_t start = std::clock();

    long long nsum = 0;
    long long dsum = 0;
    long numerator, denominator;
    for (int i = 0; i<1000000; ++i){
        if (f(a, numerator, denominator)){
            nsum += numerator;
            dsum += denominator;
        }
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "nsum: " << nsum << endl;
    cout << "dsum: " << dsum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    double num = 3.14159265359;

    long numerator, denominator;
    // gcd_method(num, numerator, denominator);
    // cout << numerator << " / " << denominator << endl;
    // timeit(gcd_method, num);


    // binary_search_method(num, numerator, denominator);
    // cout << numerator << " / " << denominator << " = " << ((double) numerator / denominator) << endl;
    // timeit(binary_search_method, num);

    if (algo_method(num, numerator, denominator)){
        cout << std::setprecision(16) << numerator << " / " << denominator << " = " << ((double) numerator / denominator) << endl;
    }
    else{
        cout << "Could not find fraction for " << num << endl;
    }
    timeit(algo_method, num);
}
