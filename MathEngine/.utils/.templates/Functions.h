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


// Predefined
#define OPERATOR_PRINT_POSTFIX_DEFINITION(OP)                                           \
    std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty){    \
        auto l = args.next();                                                           \
        auto r = args.next();                                                           \
        out << "(";                                                                     \
        l->print(out, pretty) << ")" << OP;                                             \
        out << "(";                                                                     \
        r->print(out, pretty) << ")";                                                   \
        return out;                                                                     \
    }                                                                                   \
    std::ostream& postfix(std::ostream& out, Function::Args& args){                     \
        auto l = args.next();                                                           \
        auto r = args.next();                                                           \
        l->postfix(out) << ' ';                                                         \
        r->postfix(out) << ' ';                                                         \
        return out << OP;                                                               \
    }


// Declarations
typedef expression(*FunctionConstructor)(int functionIndex, const expression arg);
namespace Function{
    #define DECLARE_FUNCTION_EXPRESSION(name) \
        expression make_fe_##name(int functionIndex, const expression arg);

	{declarations}

    #undef DECLARE_FUNCTION_EXPRESSION
}


#endif // __FUNCTION_DIRECTORY_H__
