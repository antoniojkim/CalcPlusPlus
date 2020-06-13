
#include <cmath>

#include <gsl/gsl_math.h>

#include "Numeric.h"

using namespace std;

int compare(double n1, double n2, double precision){
    if (gsl_isnan(n1) || gsl_isnan(n2)){
        return (gsl_isnan(n1) && gsl_isnan(n2)) ? 0 : -1;
    }
    if (std::trunc(n1) == n1 &&
        std::trunc(n2) == n2 &&
        std::trunc(n1) == std::trunc(n2)){
        return 0;
    }
    return gsl_fcmp(n1, n2, precision);
}
int compare(const gsl_complex& c1, const gsl_complex& c2, double precision){
    int cmp = compare(GSL_REAL(c1), GSL_REAL(c2), precision);
    if (cmp == 0){
        return compare(GSL_IMAG(c1), GSL_IMAG(c2), precision);
    }
    return cmp;
}
bool operator==(const gsl_complex& c1, const gsl_complex& c2){
    return compare(c1, c2) == 0;
}
bool operator!=(const gsl_complex& c1, const gsl_complex& c2){
    return compare(c1, c2) != 0;
}
