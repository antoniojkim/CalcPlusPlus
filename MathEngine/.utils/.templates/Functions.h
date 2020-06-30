#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "../Utils/BinarySearch.h"
#include "AbstractFunction.h"

namespace Functions {
    constexpr const int numFunctions = {numFunctions};
    constexpr const char* names[numFunctions] = {
        {names}
    };

    BINARY_SEARCH_INDEX_OF(names, numFunctions)

    const Function::AbstractFunction* getFunction(const char* name);
    const Function::AbstractFunction* getFunction(const int index);
}

#endif // __FUNCTION_DIRECTORY_H__
