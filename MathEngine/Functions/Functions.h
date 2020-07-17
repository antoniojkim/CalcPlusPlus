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
    constexpr const int numFunctions = 130;
    constexpr const char* names[numFunctions] = {
        "%", "&", "*", "**", "+", "-", "/", "//", ":=", "<-", "<<", "=", ">>", "Beta",
		"Betainc", "Cholesky", "LU", "LUsolve", "^", "^|", "abs", "absdev", "acos", "acosh",
		"acot", "acoth", "acsc", "acsch", "add", "argmax", "argmin", "asec", "asech", "asin",
		"asinh", "atan", "atanh", "bin", "bitwise_and", "bitwise_or", "bitwise_xor", "cb",
		"cbrt", "choose", "cos", "cosh", "cot", "coth", "csc", "csch", "cubic", "cubicc", "deg",
		"deriv", "det", "dfact", "diff", "div", "eq", "exp", "exp2", "expm1", "fact", "fcmp",
		"fft", "floordiv", "frexp", "gamma", "gamma_inc", "gamma_inc_P", "gamma_inc_Q",
		"gammainv", "gammastar", "gcd", "hex", "hypot", "ifft", "integral", "kurtosis", "lag1",
		"lcm", "ldexp", "ln", "ln1p", "ln2", "lnBeta", "lnchoose", "lndet", "lndfact", "lnfact",
		"lngamma", "lnpermute", "lnpoch", "log", "log1pm", "logabs", "logn", "lshift", "max",
		"mean", "median", "min", "mod", "mul", "neg", "num", "permute", "poch", "pochrel",
		"pow", "quad", "quadc", "rad", "rand", "rshift", "sd", "sec", "sech", "sin", "sinh",
		"skew", "sqr", "sqrt", "sub", "tan", "tanh", "taylorcoeff", "tss", "var", "|"
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
namespace functions{
    #define DECLARE_FUNCTION_EXPRESSION(name) \
        expression make_fe_##name(int functionIndex, const expression arg);

	DECLARE_FUNCTION_EXPRESSION(Beta);
	DECLARE_FUNCTION_EXPRESSION(Betainc);
	DECLARE_FUNCTION_EXPRESSION(Cholesky);
	DECLARE_FUNCTION_EXPRESSION(LU);
	DECLARE_FUNCTION_EXPRESSION(LUsolve);
	DECLARE_FUNCTION_EXPRESSION(abs);
	DECLARE_FUNCTION_EXPRESSION(absdev);
	DECLARE_FUNCTION_EXPRESSION(acos);
	DECLARE_FUNCTION_EXPRESSION(acosh);
	DECLARE_FUNCTION_EXPRESSION(acot);
	DECLARE_FUNCTION_EXPRESSION(acoth);
	DECLARE_FUNCTION_EXPRESSION(acsc);
	DECLARE_FUNCTION_EXPRESSION(acsch);
	DECLARE_FUNCTION_EXPRESSION(add);
	DECLARE_FUNCTION_EXPRESSION(argmax);
	DECLARE_FUNCTION_EXPRESSION(argmin);
	DECLARE_FUNCTION_EXPRESSION(asec);
	DECLARE_FUNCTION_EXPRESSION(asech);
	DECLARE_FUNCTION_EXPRESSION(asin);
	DECLARE_FUNCTION_EXPRESSION(asinh);
	DECLARE_FUNCTION_EXPRESSION(atan);
	DECLARE_FUNCTION_EXPRESSION(atanh);
	DECLARE_FUNCTION_EXPRESSION(bin);
	DECLARE_FUNCTION_EXPRESSION(bitwise_and);
	DECLARE_FUNCTION_EXPRESSION(bitwise_or);
	DECLARE_FUNCTION_EXPRESSION(bitwise_xor);
	DECLARE_FUNCTION_EXPRESSION(cb);
	DECLARE_FUNCTION_EXPRESSION(cbrt);
	DECLARE_FUNCTION_EXPRESSION(choose);
	DECLARE_FUNCTION_EXPRESSION(cos);
	DECLARE_FUNCTION_EXPRESSION(cosh);
	DECLARE_FUNCTION_EXPRESSION(cot);
	DECLARE_FUNCTION_EXPRESSION(coth);
	DECLARE_FUNCTION_EXPRESSION(csc);
	DECLARE_FUNCTION_EXPRESSION(csch);
	DECLARE_FUNCTION_EXPRESSION(cubic);
	DECLARE_FUNCTION_EXPRESSION(cubicc);
	DECLARE_FUNCTION_EXPRESSION(deg);
	DECLARE_FUNCTION_EXPRESSION(deriv);
	DECLARE_FUNCTION_EXPRESSION(det);
	DECLARE_FUNCTION_EXPRESSION(dfact);
	DECLARE_FUNCTION_EXPRESSION(diff);
	DECLARE_FUNCTION_EXPRESSION(div);
	DECLARE_FUNCTION_EXPRESSION(eq);
	DECLARE_FUNCTION_EXPRESSION(exp);
	DECLARE_FUNCTION_EXPRESSION(exp2);
	DECLARE_FUNCTION_EXPRESSION(expm1);
	DECLARE_FUNCTION_EXPRESSION(fact);
	DECLARE_FUNCTION_EXPRESSION(fcmp);
	DECLARE_FUNCTION_EXPRESSION(fft);
	DECLARE_FUNCTION_EXPRESSION(floordiv);
	DECLARE_FUNCTION_EXPRESSION(frexp);
	DECLARE_FUNCTION_EXPRESSION(gamma);
	DECLARE_FUNCTION_EXPRESSION(gamma_inc);
	DECLARE_FUNCTION_EXPRESSION(gamma_inc_P);
	DECLARE_FUNCTION_EXPRESSION(gamma_inc_Q);
	DECLARE_FUNCTION_EXPRESSION(gammainv);
	DECLARE_FUNCTION_EXPRESSION(gammastar);
	DECLARE_FUNCTION_EXPRESSION(gcd);
	DECLARE_FUNCTION_EXPRESSION(hex);
	DECLARE_FUNCTION_EXPRESSION(hypot);
	DECLARE_FUNCTION_EXPRESSION(ifft);
	DECLARE_FUNCTION_EXPRESSION(integral);
	DECLARE_FUNCTION_EXPRESSION(kurtosis);
	DECLARE_FUNCTION_EXPRESSION(lag1);
	DECLARE_FUNCTION_EXPRESSION(lcm);
	DECLARE_FUNCTION_EXPRESSION(ldexp);
	DECLARE_FUNCTION_EXPRESSION(ln);
	DECLARE_FUNCTION_EXPRESSION(ln1p);
	DECLARE_FUNCTION_EXPRESSION(ln2);
	DECLARE_FUNCTION_EXPRESSION(lnBeta);
	DECLARE_FUNCTION_EXPRESSION(lnchoose);
	DECLARE_FUNCTION_EXPRESSION(lndet);
	DECLARE_FUNCTION_EXPRESSION(lndfact);
	DECLARE_FUNCTION_EXPRESSION(lnfact);
	DECLARE_FUNCTION_EXPRESSION(lngamma);
	DECLARE_FUNCTION_EXPRESSION(lnpermute);
	DECLARE_FUNCTION_EXPRESSION(lnpoch);
	DECLARE_FUNCTION_EXPRESSION(log);
	DECLARE_FUNCTION_EXPRESSION(log1pm);
	DECLARE_FUNCTION_EXPRESSION(logabs);
	DECLARE_FUNCTION_EXPRESSION(logn);
	DECLARE_FUNCTION_EXPRESSION(lshift);
	DECLARE_FUNCTION_EXPRESSION(max);
	DECLARE_FUNCTION_EXPRESSION(mean);
	DECLARE_FUNCTION_EXPRESSION(median);
	DECLARE_FUNCTION_EXPRESSION(min);
	DECLARE_FUNCTION_EXPRESSION(mod);
	DECLARE_FUNCTION_EXPRESSION(mul);
	DECLARE_FUNCTION_EXPRESSION(neg);
	DECLARE_FUNCTION_EXPRESSION(num);
	DECLARE_FUNCTION_EXPRESSION(permute);
	DECLARE_FUNCTION_EXPRESSION(poch);
	DECLARE_FUNCTION_EXPRESSION(pochrel);
	DECLARE_FUNCTION_EXPRESSION(pow);
	DECLARE_FUNCTION_EXPRESSION(quad);
	DECLARE_FUNCTION_EXPRESSION(quadc);
	DECLARE_FUNCTION_EXPRESSION(rad);
	DECLARE_FUNCTION_EXPRESSION(rand);
	DECLARE_FUNCTION_EXPRESSION(rshift);
	DECLARE_FUNCTION_EXPRESSION(sd);
	DECLARE_FUNCTION_EXPRESSION(sec);
	DECLARE_FUNCTION_EXPRESSION(sech);
	DECLARE_FUNCTION_EXPRESSION(sin);
	DECLARE_FUNCTION_EXPRESSION(sinh);
	DECLARE_FUNCTION_EXPRESSION(skew);
	DECLARE_FUNCTION_EXPRESSION(sqr);
	DECLARE_FUNCTION_EXPRESSION(sqrt);
	DECLARE_FUNCTION_EXPRESSION(sub);
	DECLARE_FUNCTION_EXPRESSION(tan);
	DECLARE_FUNCTION_EXPRESSION(tanh);
	DECLARE_FUNCTION_EXPRESSION(taylorcoeff);
	DECLARE_FUNCTION_EXPRESSION(tss);
	DECLARE_FUNCTION_EXPRESSION(var);

    #undef DECLARE_FUNCTION_EXPRESSION
}


#endif // __FUNCTION_DIRECTORY_H__
