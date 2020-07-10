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
    constexpr const int numFunctions = 175;
    constexpr const char* names[numFunctions] = {
        "%", "&", "*", "**", "+", "-", "/", "//", ":=", "<-", "<<", "=", ">>", "Beta",
		"Betainc", "C", "Cholesky", "LU", "LUsolve", "P", "^", "^|", "abs", "absdev", "acos",
		"acosh", "acot", "acoth", "acsc", "acsch", "add", "arccos", "arccosh", "arccot",
		"arccoth", "arccsc", "arccsch", "arcos", "arcosh", "arcot", "arcoth", "arcsc", "arcsch",
		"arcsec", "arcsech", "arcsin", "arcsinh", "arctan", "arctanh", "argmax", "argmin",
		"arsec", "arsech", "arsin", "arsinh", "artan", "artanh", "asec", "asech", "asin",
		"asinh", "atan", "atanh", "autocorr", "bin", "bitwise_and", "bitwise_or", "bitwise_xor",
		"cb", "cbrt", "choose", "comb", "cos", "cosh", "cot", "coth", "csc", "csch", "cubic",
		"cubicc", "deg", "deriv", "det", "dfact", "diff", "div", "eq", "exp", "exp2", "expm1",
		"fact", "fcmp", "fft", "floordiv", "frexp", "gamma", "gamma_inc", "gamma_inc_P",
		"gamma_inc_Q", "gammainc", "gammaincp", "gammaincq", "gammainv", "gammastar", "gcd",
		"hex", "hypot", "ifft", "integral", "kurt", "kurtosis", "lag1", "lcm", "ldexp", "ln",
		"ln1p", "ln2", "lnBeta", "lnchoose", "lncomb", "lndet", "lndfact", "lnfact", "lngamma",
		"lnperm", "lnpermute", "lnpoch", "log", "log10", "log1p", "log1pm", "log2", "logabs",
		"logn", "lshift", "max", "max_index", "mean", "median", "min", "min_index", "mod",
		"mul", "neg", "num", "perm", "permute", "poch", "pochrel", "pow", "quad", "quadc",
		"rad", "rand", "random", "rshift", "sd", "sec", "sech", "sin", "sinh", "skew", "solve",
		"sqr", "sqrt", "std", "stdev", "sub", "tan", "tanh", "taylorcoeff", "tss", "var",
		"variance", "|"
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

	namespace gamma {
		VALUE_DECLARATION_P()
	}
	namespace lngamma {
		VALUE_DECLARATION_P()
	}
	namespace gammastar {
		VALUE_DECLARATION_P()
	}
	namespace gammainv {
		VALUE_DECLARATION_P()
	}
	namespace fact {
		VALUE_DECLARATION()
	}
	namespace dfact {
		VALUE_DECLARATION()
	}
	namespace lnfact {
		VALUE_DECLARATION()
	}
	namespace lndfact {
		VALUE_DECLARATION()
	}
	namespace choose {
		EVAL_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace lnchoose {
		EVAL_DECLARATION()
	}
	namespace permute {
		EVAL_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace lnpermute {
		EVAL_DECLARATION()
	}
	namespace taylorcoeff {
		EVAL_DECLARATION()
	}
	namespace poch {
		EVAL_DECLARATION()
	}
	namespace lnpoch {
		EVAL_DECLARATION()
	}
	namespace pochrel {
		EVAL_DECLARATION()
	}
	namespace gamma_inc {
		EVAL_DECLARATION()
	}
	namespace gamma_inc_Q {
		EVAL_DECLARATION()
	}
	namespace gamma_inc_P {
		EVAL_DECLARATION()
	}
	namespace Beta {
		EVAL_DECLARATION()
	}
	namespace lnBeta {
		EVAL_DECLARATION()
	}
	namespace Betainc {
		EVAL_DECLARATION()
	}
	namespace rand {
		EVAL_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace quad {
		EVAL_DECLARATION()
	}
	namespace quadc {
		EVAL_DECLARATION()
	}
	namespace cubic {
		EVAL_DECLARATION()
	}
	namespace cubicc {
		EVAL_DECLARATION()
	}
	namespace fft {
		EVAL_DECLARATION()
	}
	namespace ifft {
		EVAL_DECLARATION()
	}
	namespace mean {
		STAT_EVAL_DECLARATION()
	}
	namespace var {
		EVAL_DECLARATION()
	}
	namespace sd {
		EVAL_DECLARATION()
	}
	namespace tss {
		STAT_EVAL_DECLARATION()
	}
	namespace absdev {
		STAT_EVAL_DECLARATION()
	}
	namespace skew {
		STAT_EVAL_DECLARATION()
	}
	namespace kurtosis {
		STAT_EVAL_DECLARATION()
	}
	namespace lag1 {
		STAT_EVAL_DECLARATION()
	}
	namespace max {
		STAT_EVAL_DECLARATION()
	}
	namespace min {
		STAT_EVAL_DECLARATION()
	}
	namespace argmax {
		STAT_EVAL_DECLARATION()
	}
	namespace argmin {
		STAT_EVAL_DECLARATION()
	}
	namespace median {
		STAT_EVAL_DECLARATION()
	}
	namespace exp {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace exp2 {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace expm1 {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace ln {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace ln2 {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace ln1p {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace log {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace log1pm {
		VALUE_DECLARATION_P()
	}
	namespace logabs {
		VALUE_DECLARATION_P()
	}
	namespace logn {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
	}
	namespace sin {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace cos {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace tan {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace asin {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace acos {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace atan {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace sinh {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace cosh {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace tanh {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace asinh {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace acosh {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace atanh {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace csc {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace sec {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace cot {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace acsc {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace asec {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace acot {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace csch {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace sech {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace coth {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace acsch {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace asech {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace acoth {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace deriv {
		EVAL_DECLARATION()
	}
	namespace diff {
		EVAL_DECLARATION()
	}
	namespace integral {
		EVAL_DECLARATION()
	}
	namespace neg {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace frexp {
		EVAL_DECLARATION()
	}
	namespace num {
		EVAL_DECLARATION()
		VALUE_DECLARATION()
	}
	namespace hex {
		EVAL_DECLARATION()
	}
	namespace bin {
		EVAL_DECLARATION()
	}
	namespace abs {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace sqr {
		DERIVATIVE_DECLARATION()
		PRINT_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace sqrt {
		DERIVATIVE_DECLARATION()
		PRINT_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace cb {
		DERIVATIVE_DECLARATION()
		PRINT_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace cbrt {
		DERIVATIVE_DECLARATION()
		VALUE_DECLARATION_P()
	}
	namespace rad {
		VALUE_DECLARATION()
	}
	namespace deg {
		VALUE_DECLARATION()
	}
	namespace hypot {
		EVAL_DECLARATION()
	}
	namespace ldexp {
		EVAL_DECLARATION()
	}
	namespace fcmp {
		EVAL_DECLARATION()
	}
	namespace gcd {
		EVAL_DECLARATION()
	}
	namespace lcm {
		EVAL_DECLARATION()
	}
	namespace det {
		EVAL_DECLARATION()
	}
	namespace lndet {
		EVAL_DECLARATION()
	}
	namespace LU {
		EVAL_DECLARATION()
	}
	namespace LUsolve {
		EVAL_DECLARATION()
	}
	namespace Cholesky {
		EVAL_DECLARATION()
	}
	namespace div {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace mod {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace floordiv {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace mul {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace eq {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace sub {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
		SIMPLIFY_DECLARATION()
	}
	namespace lshift {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace rshift {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace bitwise_and {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace bitwise_or {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace bitwise_xor {
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace pow {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace add {
		DERIVATIVE_DECLARATION()
		EVAL_DECLARATION()
		POSTFIX_DECLARATION()
		PRINT_DECLARATION()
		SIMPLIFY_DECLARATION()
	}

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
