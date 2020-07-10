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


// Predefined
#define OPERATOR_PRINT_POSTFIX_DEFINITION(OP)                                           \
    std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty){    \
        auto l = args.next();                                                           \
        auto r = args.next();                                                           \
        l->print(out, pretty) << OP;                                                    \
        r->print(out, pretty);                                                          \
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
namespace Function {
    #define EVAL_DECLARATION() expression eval(Function::Args& args);
    #define EVAL_DECLARATION_P() extern expression (*eval)(Function::Args&);
    #define STAT_EVAL_DECLARATION() EVAL_DECLARATION()
    #define VALUE_DECLARATION() double value(double x);
    #define VALUE_DECLARATION_P() extern double (*value)(double);
    #define SIMPLIFY_DECLARATION() expression simplify(Function::Args& args);
    #define SIMPLIFY_DECLARATION_P() extern expression (*simplify)(Function::Args&);
    #define DERIVATIVE_DECLARATION() expression derivative(Function::Args& args, const std::string& var);
    #define DERIVATIVE_DECLARATION_P() extern expression (*derivative)(Function::Args&, const std::string&);
    #define INTEGRAL_DECLARATION() expression integral(Function::Args& args, const std::string& var);
    #define INTEGRAL_DECLARATION_P() extern expression (*integral)(Function::Args&, const std::string&);
    #define PRINT_DECLARATION() std::ostream& print(std::ostream& out, Function::Args& args, const bool pretty);
    #define PRINT_DECLARATION_P() extern std::ostream& (*print)(std::ostream&, Function::Args&, const bool);
    #define POSTFIX_DECLARATION() std::ostream& postfix(std::ostream& out, Function::Args& args);
    #define POSTFIX_DECLARATION_P() extern std::ostream& (*postfix)(std::ostream&, Function::Args&);

{declarations}

    #undef EVAL_DECLARATION
    #undef EVAL_DECLARATION_P
    #undef STAT_EVAL_DECLARATION
    #undef VALUE_DECLARATION
    #undef VALUE_DECLARATION_P
    #undef SIMPLIFY_DECLARATION
    #undef SIMPLIFY_DECLARATION_P
    #undef DERIVATIVE_DECLARATION
    #undef DERIVATIVE_DECLARATION_P
    #undef INTEGRAL_DECLARATION
    #undef INTEGRAL_DECLARATION_P
    #undef PRINT_DECLARATION
    #undef PRINT_DECLARATION_P
    #undef POSTFIX_DECLARATION
    #undef POSTFIX_DECLARATION_P
}

#endif // __FUNCTION_DIRECTORY_H__
