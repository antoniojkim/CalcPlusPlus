
#include "Functions.h"
#include "../Expressions/Constants.h"
#include "../Utils/Exception.h"

namespace calcpp {

    constexpr const int numFunctions =
        // begin sourcegen numFunctions
        182
        // end sourcegen
        ;
    constexpr const char* functionNames[numFunctions] = {
        // begin sourcegen functionNames
        "Beta", "Betainc", "C", "Eig", "LU", "LUsolve", "P", "QR", "SVD", "abs",
        "absdev", "acos", "acosh", "acot", "acoth", "acsc", "acsch", "arccos",
        "arccosh", "arccot", "arccoth", "arccsc", "arccsch", "arcos", "arcosh",
        "arcot", "arcoth", "arcsc", "arcsch", "arcsec", "arcsech", "arcsin",
        "arcsinh", "arctan", "arctanh", "argmax", "argmin", "arsec", "arsech",
        "arsin", "arsinh", "artan", "artanh", "asec", "asech", "asin", "asinh",
        "atan", "atanh", "autocorr", "bin", "cb", "cbrt", "chisq", "chisq_P",
        "chisq_Pinv", "chisq_Q", "chisq_Qinv", "chisq_pdf", "choose", "cnorm",
        "cnormal", "cnormalinv", "cnorminv", "comb", "cos", "cosh", "cot",
        "coth", "csc", "csch", "cubic", "cubicc", "deg", "deriv", "det",
        "dfact", "diff", "eig", "eigen", "exp", "exp2", "exp_P", "exp_Pinv",
        "exp_Q", "exp_Qinv", "exp_pdf", "expm1", "exponential", "exponential_P",
        "exponential_Pinv", "exponential_Q", "exponential_Qinv",
        "exponential_pdf", "fact", "fcmp", "fft", "frexp", "gamma", "gamma_inc",
        "gamma_inc_P", "gamma_inc_Q", "gammainc", "gammaincp", "gammaincq",
        "gammainv", "gammastar", "gauss_P", "gauss_Pinv", "gauss_Q",
        "gauss_Qinv", "gauss_pdf", "gaussian", "gcd", "hex", "hypot", "ifft",
        "integral", "kurt", "kurtosis", "lag1", "lcm", "ldexp", "ln", "ln1p",
        "ln2", "lnBeta", "lnchoose", "lncomb", "lndet", "lndfact", "lnfact",
        "lngamma", "lnperm", "lnpermute", "lnpoch", "log", "log10", "log1p",
        "log1pm", "log2", "logabs", "logn", "max", "max_index", "mean",
        "median", "min", "min_index", "neg", "normal", "normalinv", "norminv",
        "num", "perm", "permute", "poch", "pochrel", "quad", "quadc", "rad",
        "rand", "randn", "random", "sd", "sec", "sech", "sigmoid", "sin",
        "sinh", "skew", "solve", "sqr", "sqrt", "std", "stdev", "tan", "tanh",
        "taylorcoeff", "tss", "var", "variance"
        // end sourcegen
    };

    BINARY_SEARCH_INDEX_OF(functionNames, numFunctions)

    namespace functions {
        constexpr const expression functionExprs[numFunctions] = {
            // begin sourcegen functionExprs
            Beta, Betainc, choose, Eig, LU, LUsolve, permute, QR, SVD, abs,
            absdev, acos, acosh, acot, acoth, acsc, acsch, acos, acosh, acot,
            acoth, acsc, acsch, acos, acosh, acot, acoth, acsc, acsch, asec,
            asech, asin, asinh, atan, atanh, argmax, argmin, asec, asech, asin,
            asinh, atan, atanh, asec, asech, asin, asinh, atan, atanh, lag1,
            bin, cb, cbrt, chisq, chisq_P, chisq_Pinv, chisq_Q, chisq_Qinv,
            chisq_pdf, choose, gauss_Q, gauss_Q, gauss_Qinv, gauss_Qinv, choose,
            cos, cosh, cot, coth, csc, csch, cubic, cubicc, deg, deriv, det,
            dfact, diff, Eig, Eig, exp, exp2, exponential_P, exponential_Pinv,
            exponential_Q, exponential_Qinv, exponential_pdf, expm1,
            exponential, exponential_P, exponential_Pinv, exponential_Q,
            exponential_Qinv, exponential_pdf, fact, fcmp, fft, frexp, gamma,
            gamma_inc, gamma_inc_P, gamma_inc_Q, gamma_inc, gamma_inc_P,
            gamma_inc_Q, gammainv, gammastar, gauss_P, gauss_Pinv, gauss_Q,
            gauss_Qinv, gauss_pdf, randn, gcd, hex, hypot, ifft, integral,
            kurtosis, kurtosis, lag1, lcm, ldexp, ln, ln1p, ln2, lnBeta,
            lnchoose, lnchoose, lndet, lndfact, lnfact, lngamma, lnpermute,
            lnpermute, lnpoch, log, log, ln1p, log1pm, ln2, logabs, logn, max,
            argmax, mean, median, min, argmin, neg, gauss_P, gauss_Pinv,
            gauss_Pinv, num, permute, permute, poch, pochrel, quad, quadc, rad,
            rand, randn, rand, sd, sec, sech, sigmoid, sin, sinh, skew, LUsolve,
            sqr, sqrt, sd, sd, tan, tanh, taylorcoeff, tss, var, var
            // end sourcegen
        };
    }

    expression function(const std::string& name) {
        int index = indexOf(name.c_str());
        if (index == -1) { return None; }

        return functions::functionExprs[index];
    }
}  // namespace calcpp
