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
    constexpr const int numFunctions = 142;
    constexpr const char* names[numFunctions] = {
        "Beta", "Betainc", "Cholesky", "LU", "LUsolve", "abs", "absdev", "acos", "acosh",
		"acot", "acoth", "acsc", "acsch", "arccos", "arccosh", "arccot", "arccoth", "arccsc",
		"arccsch", "arcos", "arcosh", "arcot", "arcoth", "arcsc", "arcsch", "arcsec", "arcsech",
		"arcsin", "arcsinh", "arctan", "arctanh", "argmax", "argmin", "arsec", "arsech",
		"arsin", "arsinh", "artan", "artanh", "asec", "asech", "asin", "asinh", "atan", "atanh",
		"autocorr", "bin", "cb", "cbrt", "choose", "comb", "cos", "cosh", "cot", "coth", "csc",
		"csch", "cubic", "cubicc", "deg", "deriv", "det", "dfact", "diff", "exp", "exp2",
		"expm1", "fact", "fcmp", "fft", "frexp", "gamma", "gamma_inc", "gamma_inc_P",
		"gamma_inc_Q", "gammainc", "gammaincp", "gammaincq", "gammainv", "gammastar", "gcd",
		"hex", "hypot", "ifft", "integral", "kurt", "kurtosis", "lag1", "lcm", "ldexp", "ln",
		"ln1p", "ln2", "lnBeta", "lnchoose", "lncomb", "lndet", "lndfact", "lnfact", "lngamma",
		"lnperm", "lnpermute", "lnpoch", "log", "log10", "log1p", "log1pm", "log2", "logabs",
		"logn", "max", "max_index", "mean", "median", "min", "min_index", "neg", "num", "perm",
		"permute", "poch", "pochrel", "quad", "quadc", "rad", "sd", "sec", "sech", "sin",
		"sinh", "skew", "solve", "sqr", "sqrt", "std", "stdev", "tan", "tanh", "taylorcoeff",
		"tss", "var", "variance"
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
    #define POSTFIX_DECLARATION() std::ostream& postfix(std::ostream& out, Function::Args& args);

	namespace gamma {
		VALUE_DECLARATION_2()
	}
	namespace lngamma {
		VALUE_DECLARATION_2()
	}
	namespace gammastar {
		VALUE_DECLARATION_2()
	}
	namespace gammainv {
		VALUE_DECLARATION_2()
	}
	namespace fact {
		VALUE_DECLARATION_1()
	}
	namespace dfact {
		VALUE_DECLARATION_1()
	}
	namespace lnfact {
		VALUE_DECLARATION_1()
	}
	namespace lndfact {
		VALUE_DECLARATION_1()
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
		EVAL_DECLARATION()
	}
	namespace var {
		EVAL_DECLARATION()
	}
	namespace sd {
		EVAL_DECLARATION()
	}
	namespace tss {
		EVAL_DECLARATION()
	}
	namespace absdev {
		EVAL_DECLARATION()
	}
	namespace skew {
		EVAL_DECLARATION()
	}
	namespace kurtosis {
		EVAL_DECLARATION()
	}
	namespace lag1 {
		EVAL_DECLARATION()
	}
	namespace max {
		EVAL_DECLARATION()
	}
	namespace min {
		EVAL_DECLARATION()
	}
	namespace argmax {
		EVAL_DECLARATION()
	}
	namespace argmin {
		EVAL_DECLARATION()
	}
	namespace median {
		EVAL_DECLARATION()
	}
	namespace exp {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace exp2 {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace expm1 {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace ln {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace ln2 {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace ln1p {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace log {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace log1pm {
		VALUE_DECLARATION_2()
	}
	namespace logabs {
		VALUE_DECLARATION_2()
	}
	namespace logn {
		EVAL_DECLARATION()
		DERIVATIVE_DECLARATION()
	}
	namespace sin {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace cos {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace tan {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace asin {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace acos {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace atan {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace sinh {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace cosh {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace tanh {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace asinh {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace acosh {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace atanh {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace csc {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace sec {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace cot {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace acsc {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace asec {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace acot {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace csch {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace sech {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace coth {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace acsch {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace asech {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace acoth {
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
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
		EVAL_DECLARATION()
		VALUE_DECLARATION_1()
		DERIVATIVE_DECLARATION()
	}
	namespace frexp {
		EVAL_DECLARATION()
	}
	namespace num {
		EVAL_DECLARATION()
		VALUE_DECLARATION_1()
	}
	namespace hex {
		EVAL_DECLARATION()
	}
	namespace bin {
		EVAL_DECLARATION()
	}
	namespace abs {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace sqr {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace sqrt {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace cb {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
		PRINT_DECLARATION()
	}
	namespace cbrt {
		VALUE_DECLARATION_2()
		DERIVATIVE_DECLARATION()
	}
	namespace rad {
		VALUE_DECLARATION_1()
	}
	namespace deg {
		VALUE_DECLARATION_1()
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

    #undef EVAL_DECLARATION
    #undef VALUE_DECLARATION_1
    #undef VALUE_DECLARATION_2
    #undef SIMPLIFY_DECLARATION
    #undef DERIVATIVE_DECLARATION
    #undef INTEGRAL_DECLARATION
    #undef PRINT_DECLARATION
    #undef POSTFIX_DECLARATION
}

#endif // __FUNCTION_DIRECTORY_H__
