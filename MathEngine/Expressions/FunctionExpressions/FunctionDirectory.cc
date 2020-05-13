
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "Functions.h"
#include "MultiFunctions/Basic.h"
#include "MultiFunctions/Calculus.h"
#include "MultiFunctions/ExpLogFunctions.h"
#include "MultiFunctions/Random.h"
#include "MultiFunctions/SpecialFunctions.h"
#include "MultiFunctions/Statistics.h"
#include "MultiFunctionExprs/calculus.h"
#include "MultiFunctionExprs/fft.h"
#include "MultiFunctionExprs/polynomial.h"
#include "MultiFunctionExprs/tuple.h"
#include "UnaryFunctions/BasicFunctions.h"
#include "UnaryFunctions/ExpLogFunctions.h"
#include "UnaryFunctions/SpecialFunctions.h"
#include "UnaryFunctions/TrigFunctions.h"
#include "UnaryFunctionDerivatives/BasicFunctions.h"
#include "UnaryFunctionDerivatives/ExpLogFunctions.h"
#include "UnaryFunctionDerivatives/TrigFunctions.h"
#include "UnaryFunctionExprs/basic.h"
#include "UnaryFunctionExprs/linalg.h"

using namespace std;
using Function::numFunctions;

/***************************************************
 ***************** Unary Functions *****************
 ***************************************************/

const UnaryFunction unaryFunctions[numFunctions] = {
    nullptr, nullptr, f_abs, nullptr, f_acos, f_acosh, f_acot, f_acoth, f_acsc, f_acsch,
	f_arccos, f_arccosh, f_arccot, f_arccoth, f_arccsc, f_arccsch, f_arcosh, f_arcoth,
	f_arcsch, f_arcsec, f_arcsech, f_arcsin, f_arcsinh, f_arctan, f_arctanh, nullptr,
	nullptr, f_arsech, f_arsinh, f_artanh, f_asec, f_asech, f_asin, f_asinh, f_atan,
	f_atanh, nullptr, nullptr, nullptr, nullptr, f_cb, f_cbrt, nullptr, f_cos, f_cosh,
	f_cot, f_coth, f_csc, f_csch, nullptr, nullptr, f_deg, nullptr, nullptr, f_dfact,
	nullptr, f_exp, f_exp_2, f_expm1, f_fact, nullptr, nullptr, nullptr, f_gamma, nullptr,
	nullptr, nullptr, f_gammainv, f_gammastar, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, f_ln, f_ln1p, f_ln_2, nullptr, nullptr,
	f_lndfact, f_lnfact, f_lngamma, nullptr, nullptr, f_log, f_log1p, f_log_2, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, f_rad, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	f_sec, f_sech, f_sin, f_sinh, nullptr, f_sqr, f_sqrt, nullptr, nullptr, f_tan, f_tanh,
	nullptr, nullptr, nullptr, nullptr
};

UnaryFunction get_unary_function(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function(index);
}
UnaryFunction get_unary_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (Function::numArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", Function::names[functionIndex]);
    }
    return unaryFunctions[functionIndex];
}


/***************************************************
 ************** Unary Function Exprs ***************
 ***************************************************/

const UnaryFunctionExpr unaryFunctionExprs[numFunctions] = {
    fe_Cholesky, fe_LU, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fe_bin, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, fe_det, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, fe_frexp, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, fe_hex, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, fe_neg, fe_num, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

UnaryFunctionExpr get_unary_function_expr(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function_expr(index);
}
UnaryFunctionExpr get_unary_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (Function::numArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", Function::names[functionIndex]);
    }
    return unaryFunctionExprs[functionIndex];
}


/***************************************************
 *********** Unary Function Derivatives ************
 ***************************************************/

const UnaryFunctionDerivative unaryFunctionDerivatives[numFunctions] = {
    nullptr, nullptr, fprime_abs, nullptr, fprime_acos, fprime_acosh, fprime_acot,
	fprime_acoth, fprime_acsc, fprime_acsch, fprime_arccos, fprime_arccosh, fprime_arccot,
	fprime_arccoth, fprime_arccsc, fprime_arccsch, fprime_arcosh, fprime_arcoth,
	fprime_arcsch, fprime_arcsec, fprime_arcsech, fprime_arcsin, fprime_arcsinh,
	fprime_arctan, fprime_arctanh, nullptr, nullptr, fprime_arsech, fprime_arsinh,
	fprime_artanh, fprime_asec, fprime_asech, fprime_asin, fprime_asinh, fprime_atan,
	fprime_atanh, nullptr, nullptr, nullptr, nullptr, fprime_cb, fprime_cbrt, nullptr,
	fprime_cos, fprime_cosh, fprime_cot, fprime_coth, fprime_csc, fprime_csch, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, fprime_exp, fprime_exp_2,
	fprime_expm1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fprime_ln, fprime_ln1p, fprime_ln_2, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, fprime_log, fprime_log1p, fprime_log_2,
	nullptr, nullptr, nullptr, nullptr, nullptr, fprime_neg, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, fprime_sec, fprime_sech, fprime_sin, fprime_sinh, nullptr, fprime_sqr,
	fprime_sqrt, nullptr, nullptr, fprime_tan, fprime_tanh, nullptr, nullptr, nullptr,
	nullptr
};

UnaryFunctionDerivative get_unary_function_derivative(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function_derivative(index);
}
UnaryFunctionDerivative get_unary_function_derivative(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (Function::numArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", Function::names[functionIndex]);
    }
    return unaryFunctionDerivatives[functionIndex];
}


/***************************************************
 ***************** Multi Functions *****************
 ***************************************************/

const MultiFunction multiFunctions[numFunctions] = {
    nullptr, nullptr, nullptr, f_absdev, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_argmax, f_argmin,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	f_autocorr, f_beta, f_betainc, nullptr, nullptr, nullptr, f_choose, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_deriv, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_fcmp, nullptr, nullptr, nullptr,
	f_gammainc, f_gammaincp, f_gammaincq, nullptr, nullptr, f_gcd, nullptr, f_hypot,
	nullptr, f_integral, f_kurt, f_kurtosis, f_lag1, f_lcm, f_ldexp, nullptr, nullptr,
	nullptr, f_lnbeta, f_lnchoose, nullptr, nullptr, nullptr, f_lnpermute, f_lnpoch,
	nullptr, nullptr, nullptr, f_logn, f_max, f_mean, f_median, f_min, nullptr, nullptr,
	f_permute, f_poch, f_pochrel, nullptr, nullptr, nullptr, f_rand, f_randint, f_randseed,
	f_randu, f_randup, f_rseed, f_sd, nullptr, nullptr, nullptr, nullptr, f_skew, nullptr,
	nullptr, f_std, f_stdev, nullptr, nullptr, f_taylorcoeff, f_tss, f_var, f_variance
};

MultiFunction get_multi_function(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Multi Function: ", name);
    }
    return get_multi_function(index);
}
MultiFunction get_multi_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (Function::numArgs[functionIndex] < 1 && Function::numArgs[functionIndex] != -1){
        throw Exception("Function is not Multi Arg: ", Function::names[functionIndex]);
    }
    return multiFunctions[functionIndex];
}


/***************************************************
 *************** Multi Expr Functions **************
 ***************************************************/

const MultiFunctionExpr multiFunctionExprs[numFunctions] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, fe_cubic, fe_cubicc, nullptr, nullptr, nullptr,
	nullptr, fe_diff, nullptr, nullptr, nullptr, nullptr, nullptr, fe_fft, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, fe_ifft,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, fe_quad, fe_quadc, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

MultiFunctionExpr get_multi_function_expr(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Multi Function: ", name);
    }
    return get_multi_function_expr(index);
}
MultiFunctionExpr get_multi_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (Function::numArgs[functionIndex] < 1 && Function::numArgs[functionIndex] != -1){
        throw Exception("Function is not Multi Arg: ", Function::names[functionIndex]);
    }
    return multiFunctionExprs[functionIndex];
}
