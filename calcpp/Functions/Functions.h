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
    constexpr const int numFunctions = 210;
    constexpr const char* names[numFunctions] = {
        "%", "&", "*", "**", "+", "-", "/", "//", ":=", "<-", "<<", "=", ">>", "Beta",
		"Betainc", "C", "Chol", "Cholesky", "Eig", "LU", "LUsolve", "P", "QR", "SVD", "^", "^|",
		"abs", "absdev", "acos", "acosh", "acot", "acoth", "acsc", "acsch", "add", "arccos",
		"arccosh", "arccot", "arccoth", "arccsc", "arccsch", "arcos", "arcosh", "arcot",
		"arcoth", "arcsc", "arcsch", "arcsec", "arcsech", "arcsin", "arcsinh", "arctan",
		"arctanh", "argmax", "argmin", "arsec", "arsech", "arsin", "arsinh", "artan", "artanh",
		"asec", "asech", "asin", "asinh", "atan", "atanh", "autocorr", "bin", "bitwise_and",
		"bitwise_or", "bitwise_xor", "cb", "cbrt", "chisq", "chisq_P", "chisq_Pinv", "chisq_Q",
		"chisq_Qinv", "chisq_pdf", "chol", "choose", "cnorm", "comb", "cos", "cosh", "cot",
		"coth", "csc", "csch", "cubic", "cubicc", "deg", "deriv", "det", "dfact", "diff", "div",
		"eig", "eigen", "eq", "exp", "exp2", "exp_P", "exp_Pinv", "exp_Q", "exp_Qinv", "expm1",
		"exponential", "exponential_P", "exponential_Pinv", "exponential_Q", "exponential_Qinv",
		"exponential_pdf", "fact", "fcmp", "fft", "floordiv", "frexp", "gamma", "gamma_inc",
		"gamma_inc_P", "gamma_inc_Q", "gammainc", "gammaincp", "gammaincq", "gammainv",
		"gammastar", "gauss_P", "gauss_Pinv", "gauss_Q", "gauss_Qinv", "gauss_pdf", "gaussian",
		"gcd", "hex", "hypot", "ifft", "integral", "kurt", "kurtosis", "lag1", "lcm", "ldexp",
		"ln", "ln1p", "ln2", "lnBeta", "lnchoose", "lncomb", "lndet", "lndfact", "lnfact",
		"lngamma", "lnperm", "lnpermute", "lnpoch", "log", "log10", "log1p", "log1pm", "log2",
		"logabs", "logn", "lshift", "max", "max_index", "mean", "median", "min", "min_index",
		"mod", "mul", "neg", "norm", "norminv", "norminv", "num", "perm", "permute", "poch",
		"pochrel", "pow", "quad", "quadc", "rad", "rand", "randn", "random", "rshift", "sd",
		"sec", "sech", "sigmoid", "sin", "sinh", "skew", "solve", "sqr", "sqrt", "std", "stdev",
		"sub", "tan", "tanh", "taylorcoeff", "tss", "var", "variance", "|"
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

	DECLARE_FUNCTION(Beta);
	DECLARE_FUNCTION(Betainc);
	DECLARE_FUNCTION(Cholesky);
	DECLARE_FUNCTION(Eig);
	DECLARE_FUNCTION(LU);
	DECLARE_FUNCTION(LUsolve);
	DECLARE_FUNCTION(QR);
	DECLARE_FUNCTION(SVD);
	DECLARE_FUNCTION(abs);
	DECLARE_FUNCTION(absdev);
	DECLARE_FUNCTION(acos);
	DECLARE_FUNCTION(acosh);
	DECLARE_FUNCTION(acot);
	DECLARE_FUNCTION(acoth);
	DECLARE_FUNCTION(acsc);
	DECLARE_FUNCTION(acsch);
	DECLARE_FUNCTION(add);
	DECLARE_FUNCTION(argmax);
	DECLARE_FUNCTION(argmin);
	DECLARE_FUNCTION(asec);
	DECLARE_FUNCTION(asech);
	DECLARE_FUNCTION(asin);
	DECLARE_FUNCTION(asinh);
	DECLARE_FUNCTION(atan);
	DECLARE_FUNCTION(atanh);
	DECLARE_FUNCTION(bin);
	DECLARE_FUNCTION(bitwise_and);
	DECLARE_FUNCTION(bitwise_or);
	DECLARE_FUNCTION(bitwise_xor);
	DECLARE_FUNCTION(cb);
	DECLARE_FUNCTION(cbrt);
	DECLARE_FUNCTION(chisq);
	DECLARE_FUNCTION(chisq_P);
	DECLARE_FUNCTION(chisq_Pinv);
	DECLARE_FUNCTION(chisq_Q);
	DECLARE_FUNCTION(chisq_Qinv);
	DECLARE_FUNCTION(chisq_pdf);
	DECLARE_FUNCTION(choose);
	DECLARE_FUNCTION(cos);
	DECLARE_FUNCTION(cosh);
	DECLARE_FUNCTION(cot);
	DECLARE_FUNCTION(coth);
	DECLARE_FUNCTION(csc);
	DECLARE_FUNCTION(csch);
	DECLARE_FUNCTION(cubic);
	DECLARE_FUNCTION(cubicc);
	DECLARE_FUNCTION(deg);
	DECLARE_FUNCTION(deriv);
	DECLARE_FUNCTION(det);
	DECLARE_FUNCTION(dfact);
	DECLARE_FUNCTION(diff);
	DECLARE_FUNCTION(div);
	DECLARE_FUNCTION(eq);
	DECLARE_FUNCTION(exp);
	DECLARE_FUNCTION(exp2);
	DECLARE_FUNCTION(expm1);
	DECLARE_FUNCTION(exponential);
	DECLARE_FUNCTION(exponential_P);
	DECLARE_FUNCTION(exponential_Pinv);
	DECLARE_FUNCTION(exponential_Q);
	DECLARE_FUNCTION(exponential_Qinv);
	DECLARE_FUNCTION(exponential_pdf);
	DECLARE_FUNCTION(fact);
	DECLARE_FUNCTION(fcmp);
	DECLARE_FUNCTION(fft);
	DECLARE_FUNCTION(floordiv);
	DECLARE_FUNCTION(frexp);
	DECLARE_FUNCTION(gamma);
	DECLARE_FUNCTION(gamma_inc);
	DECLARE_FUNCTION(gamma_inc_P);
	DECLARE_FUNCTION(gamma_inc_Q);
	DECLARE_FUNCTION(gammainv);
	DECLARE_FUNCTION(gammastar);
	DECLARE_FUNCTION(gauss_P);
	DECLARE_FUNCTION(gauss_Pinv);
	DECLARE_FUNCTION(gauss_Q);
	DECLARE_FUNCTION(gauss_Qinv);
	DECLARE_FUNCTION(gauss_pdf);
	DECLARE_FUNCTION(gcd);
	DECLARE_FUNCTION(hex);
	DECLARE_FUNCTION(hypot);
	DECLARE_FUNCTION(ifft);
	DECLARE_FUNCTION(integral);
	DECLARE_FUNCTION(kurtosis);
	DECLARE_FUNCTION(lag1);
	DECLARE_FUNCTION(lcm);
	DECLARE_FUNCTION(ldexp);
	DECLARE_FUNCTION(ln);
	DECLARE_FUNCTION(ln1p);
	DECLARE_FUNCTION(ln2);
	DECLARE_FUNCTION(lnBeta);
	DECLARE_FUNCTION(lnchoose);
	DECLARE_FUNCTION(lndet);
	DECLARE_FUNCTION(lndfact);
	DECLARE_FUNCTION(lnfact);
	DECLARE_FUNCTION(lngamma);
	DECLARE_FUNCTION(lnpermute);
	DECLARE_FUNCTION(lnpoch);
	DECLARE_FUNCTION(log);
	DECLARE_FUNCTION(log1pm);
	DECLARE_FUNCTION(logabs);
	DECLARE_FUNCTION(logn);
	DECLARE_FUNCTION(lshift);
	DECLARE_FUNCTION(max);
	DECLARE_FUNCTION(mean);
	DECLARE_FUNCTION(median);
	DECLARE_FUNCTION(min);
	DECLARE_FUNCTION(mod);
	DECLARE_FUNCTION(mul);
	DECLARE_FUNCTION(neg);
	DECLARE_FUNCTION(num);
	DECLARE_FUNCTION(permute);
	DECLARE_FUNCTION(poch);
	DECLARE_FUNCTION(pochrel);
	DECLARE_FUNCTION(pow);
	DECLARE_FUNCTION(quad);
	DECLARE_FUNCTION(quadc);
	DECLARE_FUNCTION(rad);
	DECLARE_FUNCTION(rand);
	DECLARE_FUNCTION(randn);
	DECLARE_FUNCTION(rshift);
	DECLARE_FUNCTION(sd);
	DECLARE_FUNCTION(sec);
	DECLARE_FUNCTION(sech);
	DECLARE_FUNCTION(sigmoid);
	DECLARE_FUNCTION(sin);
	DECLARE_FUNCTION(sinh);
	DECLARE_FUNCTION(skew);
	DECLARE_FUNCTION(sqr);
	DECLARE_FUNCTION(sqrt);
	DECLARE_FUNCTION(sub);
	DECLARE_FUNCTION(tan);
	DECLARE_FUNCTION(tanh);
	DECLARE_FUNCTION(taylorcoeff);
	DECLARE_FUNCTION(tss);
	DECLARE_FUNCTION(var);

    #undef DECLARE_FUNCTION
}


#endif // __FUNCTION_DIRECTORY_H__
