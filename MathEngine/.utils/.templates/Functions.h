#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

constexpr const int numFunctions = {numFunctions};
constexpr const char* functionNames[numFunctions] = {
    {functionNames}
};
constexpr const size_t functionNameLengths[numFunctions] = {
    {functionNameLengths}
};
constexpr const size_t functionOrderByLength[numFunctions] = {
    {functionOrderByLength}
};
constexpr const int functionNumArgs[numFunctions] = {
    {functionNumArgs}
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
