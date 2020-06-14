#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "../Utils/BinarySearch.h"

class AbstractFunction;

namespace Functions {
    constexpr const int numFunctions = 142;
    constexpr const char* names[numFunctions] = {
        "Beta", "Betainc", "Cholesky", "LU", "LUsolve", "abs", "absdev", "acos", "acosh",
        "acot", "acoth", "acsc", "acsch", "arccos", "arccosh", "arccot", "arccoth", "arccsc",
        "arccsch", "arcos", "arcosh", "arcot", "arcoth", "arcsc", "arcsch", "arcsec", "arcsech",
        "arcsin", "arcsinh", "arctan", "arctanh", "argmax", "argmin", "arsec", "arsech",
        "arsin", "arsinh", "artan", "artanh", "asec", "asech", "asin", "asinh", "atan", "atanh",
        "autocorr", "bin", "cb", "cbrt", "choose", "comb", "cos", "cosh", "cot", "coth", "csc",
        "csch", "cubic", "cubicc", "deg", "deriv", "det", "dfact", "diff", "exp", "exp2",
        "expm1", "fact", "fcmp", "fft", "frexp", "gamma", "gamma_inc", "gamma_inc_P",
        "gamma_inc_Q", "gammainc", "gammaincp", "gammaincq", "gammainv", "gammastar", "gcd",
        "hex", "hypot", "ifft", "integral", "kurt", "kurtosis", "lag1", "lcm", "ldexp", "ln",
        "ln1p", "ln2", "lnBeta", "lnchoose", "lncomb", "lndet", "lndfact", "lnfact", "lngamma",
        "lnperm", "lnpermute", "lnpoch", "log", "log10", "log1p", "log1pm", "log2", "logabs",
        "logn", "max", "max_index", "mean", "median", "min", "min_index", "neg", "num", "perm",
        "permute", "poch", "pochrel", "quad", "quadc", "rad", "sd", "sec", "sech", "sin",
        "sinh", "skew", "solve", "sqr", "sqrt", "std", "stdev", "tan", "tanh", "taylorcoeff",
        "tss", "var", "variance"
    };

    BINARY_SEARCH_INDEX_OF(names, numFunctions)

    const AbstractFunction* getFunction(const char* name);
    const AbstractFunction* getFunction(const int index);
}

#endif // __FUNCTION_DIRECTORY_H__
