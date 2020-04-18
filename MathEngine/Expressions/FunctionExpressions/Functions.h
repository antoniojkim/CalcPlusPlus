#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

constexpr const int numFunctions = 104;
constexpr const char* functionNames[numFunctions] = {
    "taylorcoeff", "lnpermute", "integrate", "gammastar", "gammaincq", "gammaincp",
	"variance", "lnchoose", "kurtosis", "integral", "gammainv", "gammainc", "autocorr",
	"pochrel", "permute", "lngamma", "lndfact", "betainc", "arctanh", "arcsinh", "arcsech",
	"arccsch", "arccoth", "arccosh", "median", "lnpoch", "lnfact", "lnbeta", "cubicc",
	"choose", "artanh", "arsinh", "arsech", "argmin", "argmax", "arctan", "arcsin",
	"arcsec", "arcsch", "arcoth", "arcosh", "arccsc", "arccot", "arccos", "absdev", "stdev",
	"quadc", "log_2", "log1p", "gamma", "expm1", "exp_2", "dfact", "deriv", "cubic",
	"atanh", "asinh", "asech", "acsch", "acoth", "acosh", "tanh", "sqrt", "skew", "sinh",
	"sech", "quad", "poch", "mean", "logn", "ln_2", "ln1p", "lag1", "kurt", "fact", "csch",
	"coth", "cosh", "beta", "atan", "asin", "asec", "acsc", "acot", "acos", "var", "tss",
	"tan", "std", "sin", "sec", "neg", "min", "max", "log", "exp", "det", "csc", "cot",
	"cos", "abs", "sd", "ln", "dx"
};
constexpr const size_t functionNameLengths[numFunctions] = {
    11, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2
};
constexpr const int functionNumArgs[numFunctions] = {
    2, 2, 0, 1, 2, 2, -1, 2, -1, 3, 1, 2, -1, 2, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, -1, 2, 1, 2,
	4, 2, 1, 1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 3, 1, 1, 1, 1, 1, 1, 2, 4, 1,
	1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 3, 2, -1, 2, 1, 1, -1, -1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
	1, -1, -1, 1, -1, 1, 1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 0
};

/*
Returns index of the function in the functionNames array.

Parameters
----------
name: The name of the function

Returns
-------
The index or -1 if the provided name is not a function.
*/
constexpr int getFunctionIndex(const char* name){
    for (int i = 0; i < numFunctions; ++i){
        if (std::strcmp(name, functionNames[i]) == 0){
            return i;
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
