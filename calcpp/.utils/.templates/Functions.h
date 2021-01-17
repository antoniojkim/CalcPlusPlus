#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "../Expressions/Expression.h"
#include "../Utils/BinarySearch.h"

namespace Functions {
    constexpr const int numFunctions = {numFunctions};
    constexpr const char* names[numFunctions] = {
        {names}
    };

    BINARY_SEARCH_INDEX_OF(names, numFunctions)

    expression construct(const int functionIndex, const expression arg);

    bool isOperator(const char* name);
    bool isOperator(const int functionIndex);
}

// Declarations
typedef expression(*FunctionConstructor)(int functionIndex, const expression arg);
namespace Function{
    #define DECLARE_FUNCTION(name) \
        expression make_fe_##name(int functionIndex, const expression arg)

	{declarations}

    #undef DECLARE_FUNCTION
}


#endif // __FUNCTION_DIRECTORY_H__
