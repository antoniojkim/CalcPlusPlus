#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include <gsl/gsl_math.h>

#include "../../Utils/BinarySearch.h"

constexpr const int numConstants = {numConstants};
constexpr const char* constants[numConstants] = {
    {constants}
};
constexpr const double constantValues[numConstants] = {
    {constantValues}
};
const std::string shortConstants[numConstants] = {
    {shortConstants}
};
constexpr const char * constantLongValues[numConstants] = {
    {constantLongValues}
};
constexpr const int longestConstantName = {longestConstantName};
constexpr const int shortestConstantName = {shortestConstantName};

/*
Returns index of the constant in the constants array.

Uses binary search under the hood to search for the index.

Parameters
----------
name: The name of the constant

Returns
-------
The index or -1 if the provided name is not a constant.
*/
CONSTEXPR_BINARY_SEARCH(getConstantIndex, constants, numConstants)


/*
Returns the value of the constant at the provided index.

Parameters
----------
index: the index of the constant name

Returns
-------
If the index is valid, it will return the number of arguments.
If the index is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
static double getConstantValue(const std::string& name){
    int index = getConstantIndex(name.c_str());
    if (index != -1){
        return constantValues[index];
    }
    return GSL_NAN;
}
constexpr double getConstantValue(int index){
    if (index >= 0 && index < numConstants){
        return constantValues[index];
    }
    return GSL_NAN;
}

#endif // __CONSTANTS_H__
