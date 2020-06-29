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
    constexpr const int numFunctions = {numFunctions};
    constexpr const char* names[numFunctions] = {
        {functionNames}
    };
    constexpr const size_t nameLengths[numFunctions] = {
        {functionNameLengths}
    };
    constexpr const size_t orderByLength[numFunctions] = {
        {functionOrderByLength}
    };
    constexpr const int numArgs[numFunctions] = {
        {functionNumArgs}
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
