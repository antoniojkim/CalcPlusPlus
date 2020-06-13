#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "../../Utils/BinarySearch.h"

namespace Function {
    constexpr const int numFunctions = 127;
    constexpr const char* names[numFunctions] = {
        "Cholesky", "LU", "abs", "absdev", "acos", "acosh", "acot", "acoth", "acsc", "acsch",
        "arccos", "arccosh", "arccot", "arccoth", "arccsc", "arccsch", "arcosh", "arcoth",
        "arcsch", "arcsec", "arcsech", "arcsin", "arcsinh", "arctan", "arctanh", "argmax",
        "argmin", "arsech", "arsinh", "artanh", "asec", "asech", "asin", "asinh", "atan",
        "atanh", "autocorr", "beta", "betainc", "bin", "cb", "cbrt", "choose", "cos", "cosh",
        "cot", "coth", "csc", "csch", "cubic", "cubicc", "deg", "deriv", "det", "dfact", "diff",
        "exp", "exp_2", "expm1", "fact", "fcmp", "fft", "frexp", "gamma", "gammainc",
        "gammaincp", "gammaincq", "gammainv", "gammastar", "gcd", "hex", "hypot", "ifft",
        "integral", "kurt", "kurtosis", "lag_1", "lcm", "ldexp", "ln", "ln1p", "ln_2", "lnbeta",
        "lnchoose", "lndfact", "lnfact", "lngamma", "lnpermute", "lnpoch", "log", "log1p",
        "log_2", "logn", "max", "mean", "median", "min", "neg", "num", "permute", "poch",
        "pochrel", "quad", "quadc", "rad", "rand", "randint", "randseed", "randu", "randup",
        "rseed", "sd", "sec", "sech", "sin", "sinh", "skew", "sqr", "sqrt", "std", "stdev",
        "tan", "tanh", "taylorcoeff", "tss", "var", "variance"
    };
    constexpr const size_t nameLengths[numFunctions] = {
        8, 2, 3, 6, 4, 5, 4, 5, 4, 5, 6, 7, 6, 7, 6, 7, 6, 6, 6, 6, 7, 6, 7, 6, 7, 6, 6, 6, 6,
        6, 4, 5, 4, 5, 4, 5, 8, 4, 7, 3, 2, 4, 6, 3, 4, 3, 4, 3, 4, 5, 6, 3, 5, 3, 5, 4, 3, 5,
        5, 4, 4, 3, 5, 5, 8, 9, 9, 8, 9, 3, 3, 5, 4, 8, 4, 8, 5, 3, 5, 2, 4, 4, 6, 8, 7, 6, 7,
        9, 6, 3, 5, 5, 4, 3, 4, 6, 3, 3, 3, 7, 4, 7, 4, 5, 3, 4, 7, 8, 5, 6, 5, 2, 3, 4, 3, 4,
        4, 3, 4, 3, 5, 3, 4, 11, 3, 3, 8
    };
    constexpr const size_t orderByLength[numFunctions] = {
        123, 65, 66, 68, 87, 0, 36, 64, 67, 73, 75, 83, 107, 126, 11, 13, 15, 20, 22, 24, 38,
        84, 86, 99, 101, 106, 3, 10, 12, 14, 16, 17, 18, 19, 21, 23, 25, 26, 27, 28, 29, 42, 50,
        82, 85, 88, 95, 109, 5, 7, 9, 31, 33, 35, 49, 52, 54, 57, 58, 62, 63, 71, 76, 78, 90,
        91, 103, 108, 110, 120, 4, 6, 8, 30, 32, 34, 37, 41, 44, 46, 48, 55, 59, 60, 72, 74, 80,
        81, 92, 94, 100, 102, 105, 113, 115, 116, 118, 122, 2, 39, 43, 45, 47, 51, 53, 56, 61,
        69, 70, 77, 89, 93, 96, 97, 98, 104, 112, 114, 117, 119, 121, 124, 125, 1, 40, 79, 111
    };
    constexpr const int numArgs[numFunctions] = {
        1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, -1, 2, 3, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4, 4, 1, -1, 1, 1, -1,
        1, 1, 1, 1, -1, -1, 1, 1, 2, 2, 2, 1, 1, 2, 1, -1, -1, 3, -1, -1, -1, 2, 2, 1, 1, 1, 2,
        2, 1, 1, 1, 2, 2, 1, 1, 1, 2, -1, -1, -1, -1, 1, 1, 2, 2, 2, 3, 3, 1, -1, -1, -1, -1,
        -1, -1, -1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, 2, -1, -1, -1
    };

    BINARY_SEARCH_INDEX_OF(names, numFunctions)

    // constexpr int numArgs(int index){
    //     if (index >= 0 && index < numFunctions){
    //         return functionNumArgs[index];
    //     }
    //     return 0;
    // }
    // inline int numArgs(const std::string& name){
    //     return numArgs(indexOf(name));
    // }
}

#endif // __FUNCTION_DIRECTORY_H__
