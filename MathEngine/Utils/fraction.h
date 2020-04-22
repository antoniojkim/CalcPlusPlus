#pragma once

#include <cmath>

#include <gsl/gsl_math.h>

bool to_fraction(double num, long& numerator, long& denominator){
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
