#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

constexpr const int numFunctions = 113;
constexpr const char* functionNames[numFunctions] = {
    "abs", "absdev", "acos", "acosh", "acot", "acoth", "acsc", "acsch", "arccos", "arccosh",
	"arccot", "arccoth", "arccsc", "arccsch", "arcosh", "arcoth", "arcsch", "arcsec",
	"arcsech", "arcsin", "arcsinh", "arctan", "arctanh", "argmax", "argmin", "arsech",
	"arsinh", "artanh", "asec", "asech", "asin", "asinh", "atan", "atanh", "autocorr",
	"beta", "betainc", "cb", "cbrt", "choose", "cos", "cosh", "cot", "coth", "csc", "csch",
	"cubic", "cubicc", "deg", "deriv", "det", "dfact", "exp", "exp_2", "expm1", "fact",
	"fcmp", "fft", "frexp", "gamma", "gammainc", "gammaincp", "gammaincq", "gammainv",
	"gammastar", "hypot", "ifft", "integral", "kurt", "kurtosis", "lag1", "ldexp", "ln",
	"ln1p", "ln_2", "lnbeta", "lnchoose", "lndfact", "lnfact", "lngamma", "lnpermute",
	"lnpoch", "log", "log1p", "log_2", "logn", "max", "mean", "median", "min", "neg",
	"permute", "poch", "pochrel", "quad", "quadc", "rad", "sd", "sec", "sech", "sin",
	"sinh", "skew", "sqr", "sqrt", "std", "stdev", "tan", "tanh", "taylorcoeff", "tss",
	"var", "variance"
};
constexpr const size_t functionNameLengths[numFunctions] = {
    3, 6, 4, 5, 4, 5, 4, 5, 6, 7, 6, 7, 6, 7, 6, 6, 6, 6, 7, 6, 7, 6, 7, 6, 6, 6, 6, 6, 4,
	5, 4, 5, 4, 5, 8, 4, 7, 2, 4, 6, 3, 4, 3, 4, 3, 4, 5, 6, 3, 5, 3, 5, 3, 5, 5, 4, 4, 3,
	5, 5, 8, 9, 9, 8, 9, 5, 4, 8, 4, 8, 4, 5, 2, 4, 4, 6, 8, 7, 6, 7, 9, 6, 3, 5, 5, 4, 3,
	4, 6, 3, 3, 7, 4, 7, 4, 5, 3, 2, 3, 4, 3, 4, 4, 3, 4, 3, 5, 3, 4, 11, 3, 3, 8
};
constexpr const size_t functionOrderByLength[numFunctions] = {
    112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94,
	93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72,
	71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28,
	27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,
	4, 3, 2, 1, 0
};
constexpr const int functionNumArgs[numFunctions] = {
    1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, -1, 2, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4, 4, 1, 2, 1, 1, 1, 1, 1, 1, -1,
	-1, 1, 1, 2, 2, 2, 1, 1, -1, -1, 3, -1, -1, -1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1,
	1, 2, -1, -1, -1, -1, 1, 2, 2, 2, 3, 3, 1, -1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, 2,
	-1, -1, -1
};

/*
Returns index of the function in the functionNames array.

Uses binary search under the hood to search for the index.

Parameters
----------
name: The name of the function

Returns
-------
The index or -1 if the provided name is not a function.
*/
constexpr int getFunctionIndex(const char* name){
    int low = 0;
    int high = numFunctions - 1;
    while (true){
        if (low > high){
            return -1;
        }

        int mid = (low + high) / 2;
        int cmp = std::strcmp(name, functionNames[mid]);
        if (cmp == 0){
            return mid;
        }
        else if (cmp < 0){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return -1;
}
inline int getFunctionIndex(const std::string& name){
    return getFunctionIndex(name.c_str());
}

/*
Returns the number of arguments for the function at the provided index.

Parameters
----------
index: the index of the function name

Returns
-------
If the index is valid, it will return the number of arguments.
If the index is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
constexpr int getFunctionNumArgs(int index){
    if (index >= 0 && index < numFunctions){
        return functionNumArgs[index];
    }
    return 0;
}

/*
Returns the number of arguments that a function takes in.

Parameters
----------
name: The name of the function

Returns
-------
If the name is a valid function it will return the number of arguments.
If the name is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
inline int getFunctionNumArgs(const std::string& name){
    return getFunctionNumArgs(getFunctionIndex(name));
}

#endif // __FUNCTION_DIRECTORY_H__
