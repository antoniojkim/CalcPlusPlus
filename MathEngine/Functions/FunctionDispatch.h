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
        "exp", "exp2", "expm1", "fact", "fcmp", "fft", "frexp", "gamma", "gammainc",
        "gammaincp", "gammaincq", "gammainv", "gammastar", "gcd", "hex", "hypot", "ifft",
        "integral", "kurt", "kurtosis", "lag_1", "lcm", "ldexp", "ln", "ln1p", "ln_2", "lnbeta",
        "lnchoose", "lndfact", "lnfact", "lngamma", "lnpermute", "lnpoch", "log", "log1p",
        "log_2", "logn", "max", "mean", "median", "min", "neg", "num", "permute", "poch",
        "pochrel", "quad", "quadc", "rad", "rand", "randint", "randseed", "randu", "randup",
        "rseed", "sd", "sec", "sech", "sin", "sinh", "skew", "sqr", "sqrt", "std", "stdev",
        "tan", "tanh", "taylorcoeff", "tss", "var", "variance"
    };

    BINARY_SEARCH_INDEX_OF(names, numFunctions)
}

#endif // __FUNCTION_DIRECTORY_H__
