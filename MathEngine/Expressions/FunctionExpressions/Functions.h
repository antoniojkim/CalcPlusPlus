#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

constexpr const int numFunctions = 115;
constexpr const char* functionNames[numFunctions] = {
    "abs", "absdev", "acos", "acosh", "acot", "acoth", "acsc", "acsch", "arccos", "arccosh",
	"arccot", "arccoth", "arccsc", "arccsch", "arcosh", "arcoth", "arcsch", "arcsec",
	"arcsech", "arcsin", "arcsinh", "arctan", "arctanh", "argmax", "argmin", "arsech",
	"arsinh", "artanh", "asec", "asech", "asin", "asinh", "atan", "atanh", "autocorr",
	"beta", "betainc", "cb", "cbrt", "choose", "cos", "cosh", "cot", "coth", "csc", "csch",
	"cubic", "cubicc", "deg", "deriv", "det", "dfact", "dx", "exp", "exp_2", "expm1",
	"fact", "fcmp", "fft", "frexp", "gamma", "gammainc", "gammaincp", "gammaincq",
	"gammainv", "gammastar", "hypot", "ifft", "integral", "integrate", "kurt", "kurtosis",
	"lag1", "ldexp", "ln", "ln1p", "ln_2", "lnbeta", "lnchoose", "lndfact", "lnfact",
	"lngamma", "lnpermute", "lnpoch", "log", "log1p", "log_2", "logn", "max", "mean",
	"median", "min", "neg", "permute", "poch", "pochrel", "quad", "quadc", "rad", "sd",
	"sec", "sech", "sin", "sinh", "skew", "sqr", "sqrt", "std", "stdev", "tan", "tanh",
	"taylorcoeff", "tss", "var", "variance"
};
constexpr const size_t functionNameLengths[numFunctions] = {
    3, 6, 4, 5, 4, 5, 4, 5, 6, 7, 6, 7, 6, 7, 6, 6, 6, 6, 7, 6, 7, 6, 7, 6, 6, 6, 6, 6, 4,
	5, 4, 5, 4, 5, 8, 4, 7, 2, 4, 6, 3, 4, 3, 4, 3, 4, 5, 6, 3, 5, 3, 5, 2, 3, 5, 5, 4, 4,
	3, 5, 5, 8, 9, 9, 8, 9, 5, 4, 8, 9, 4, 8, 4, 5, 2, 4, 4, 6, 8, 7, 6, 7, 9, 6, 3, 5, 5,
	4, 3, 4, 6, 3, 3, 7, 4, 7, 4, 5, 3, 2, 3, 4, 3, 4, 4, 3, 4, 3, 5, 3, 4, 11, 3, 3, 8
};
constexpr const size_t functionOrderByLength[numFunctions] = {
    111, 62, 63, 65, 69, 82, 34, 61, 64, 68, 71, 78, 114, 9, 11, 13, 18, 20, 22, 36, 79, 81,
	93, 95, 1, 8, 10, 12, 14, 15, 16, 17, 19, 21, 23, 24, 25, 26, 27, 39, 47, 77, 80, 83,
	90, 3, 5, 7, 29, 31, 33, 46, 49, 51, 54, 55, 59, 60, 66, 73, 85, 86, 97, 108, 2, 4, 6,
	28, 30, 32, 35, 38, 41, 43, 45, 56, 57, 67, 70, 72, 75, 76, 87, 89, 94, 96, 101, 103,
	104, 106, 110, 0, 40, 42, 44, 48, 50, 53, 58, 84, 88, 91, 92, 98, 100, 102, 105, 107,
	109, 112, 113, 37, 52, 74, 99
};
constexpr const int functionNumArgs[numFunctions] = {
    1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, -1, 2, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4, 4, 1, 2, 1, 1, 0, 1, 1, 1, 1,
	-1, -1, 1, 1, 2, 2, 2, 1, 1, -1, -1, 3, 0, -1, -1, -1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2,
	1, 1, 1, 2, -1, -1, -1, -1, 1, 2, 2, 2, 3, 3, 1, -1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1,
	2, -1, -1, -1
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
