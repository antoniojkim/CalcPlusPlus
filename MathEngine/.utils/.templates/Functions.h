#pragma once

#ifndef __FUNCTION_DIRECTORY_H__
#define __FUNCTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "../Expressions/Expression.h"
#include "../Utils/Argparse.h"
#include "../Utils/BinarySearch.h"

namespace Functions {
    constexpr const int numFunctions = {numFunctions};
    constexpr const char* names[numFunctions] = {
        {names}
    };

    BINARY_SEARCH_INDEX_OF(names, numFunctions)

    #define FUNCTION_GET(Type)                    \
        const Type get##Type(const char* name);   \
        const Type get##Type(const int index);

    typedef expression (*EvalFunction)(Function::Args&);
    FUNCTION_GET(EvalFunction)

    typedef double (*ValueFunction)(double);
    FUNCTION_GET(ValueFunction)

    typedef expression (*SimplifyFunction)(Function::Args&);
    FUNCTION_GET(SimplifyFunction)

    typedef expression (*DerivativeFunction)(Function::Args&, const std::string&);
    FUNCTION_GET(DerivativeFunction)

    typedef expression (*IntegralFunction)(Function::Args&, const std::string&);
    FUNCTION_GET(IntegralFunction)

    typedef std::ostream& (*PrintFunction)(std::ostream&, Function::Args&, const bool);
    FUNCTION_GET(PrintFunction)

    typedef std::ostream& (*PostfixFunction)(std::ostream&, Function::Args&);
    FUNCTION_GET(PostfixFunction)

    #undef FUNCTION_GET

    const Function::Signature& getSignature(const char* name);
    const Function::Signature& getSignature(const int index);
}

namespace Function {
    #define EVAL_DECLARATION() expression eval(Function::Args& args);
    #define VALUE_DECLARATION_1() double value(double x);
    #define VALUE_DECLARATION_2() extern double (*value)(double);
    #define SIMPLIFY_DECLARATION() expression simplify(Function::Args& args);
    #define DERIVATIVE_DECLARATION() expression derivative(Function::Args& args, const std::string& var);
    #define INTEGRAL_DECLARATION() expression integral(Function::Args& args, const std::string& var);
    #define PRINT_DECLARATION() std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty);
    #define POSTFIX_DECLARATION_1() std::ostream& postfix(std::ostream& out, Function::Args& args);
    #define POSTFIX_DECLARATION_2() std::ostream& (*postfix)(std::ostream&, Function::Args&);

{declarations}

    #undef EVAL_DECLARATION
    #undef VALUE_DECLARATION_1
    #undef VALUE_DECLARATION_2
    #undef SIMPLIFY_DECLARATION
    #undef DERIVATIVE_DECLARATION
    #undef INTEGRAL_DECLARATION
    #undef PRINT_DECLARATION
    #undef POSTFIX_DECLARATION_1
    #undef POSTFIX_DECLARATION_2
}

#endif // __FUNCTION_DIRECTORY_H__
