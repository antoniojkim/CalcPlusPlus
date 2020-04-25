
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "Functions.h"
#include "MultiFunctions/Basic.h"
#include "MultiFunctions/Calculus.h"
#include "MultiFunctions/ExpLogFunctions.h"
#include "MultiFunctions/SpecialFunctions.h"
#include "MultiFunctions/Statistics.h"
#include "MultiFunctionExprs/fft.h"
#include "MultiFunctionExprs/polynomial.h"
#include "MultiFunctionExprs/tuple.h"
#include "UnaryFunctions/BasicFunctions.h"
#include "UnaryFunctions/ExpLogFunctions.h"
#include "UnaryFunctions/SpecialFunctions.h"
#include "UnaryFunctions/TrigFunctions.h"
#include "UnaryFunctionExprs/basic.h"
#include "UnaryFunctionExprs/linalg.h"

using namespace std;

/***************************************************
 ***************** Unary Functions *****************
 ***************************************************/

const UnaryFunction unaryFunctions[numFunctions] = {
    f_abs, nullptr, f_acos, f_acosh, f_acot, f_acoth, f_acsc, f_acsch, f_arccos, f_arccosh,
	f_arccot, f_arccoth, f_arccsc, f_arccsch, f_arcosh, f_arcoth, f_arcsch, f_arcsec,
	f_arcsech, f_arcsin, f_arcsinh, f_arctan, f_arctanh, nullptr, nullptr, f_arsech,
	f_arsinh, f_artanh, f_asec, f_asech, f_asin, f_asinh, f_atan, f_atanh, nullptr, nullptr,
	nullptr, nullptr, f_cos, f_cosh, f_cot, f_coth, f_csc, f_csch, nullptr, nullptr,
	nullptr, nullptr, f_dfact, nullptr, f_exp, f_exp_2, f_expm1, f_fact, nullptr, nullptr,
	nullptr, f_gamma, nullptr, nullptr, nullptr, f_gammainv, f_gammastar, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_ln, f_ln1p, f_ln_2, nullptr,
	nullptr, f_lndfact, f_lnfact, f_lngamma, nullptr, nullptr, f_log, f_log1p, f_log_2,
	nullptr, nullptr, nullptr, nullptr, nullptr, f_neg, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, f_sec, f_sech, f_sin, f_sinh, nullptr, f_sqrt, nullptr, nullptr,
	f_tan, f_tanh, nullptr, nullptr, nullptr, nullptr
};

UnaryFunction get_unary_function(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function(index);
}
UnaryFunction get_unary_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", functionNames[functionIndex]);
    }
    return unaryFunctions[functionIndex];
}


/***************************************************
 ************** Unary Function Exprs ***************
 ***************************************************/

const UnaryFunctionExpr unaryFunctionExprs[numFunctions] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, fe_det, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, fe_frexp, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

UnaryFunctionExpr get_unary_function_expr(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function_expr(index);
}
UnaryFunctionExpr get_unary_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", functionNames[functionIndex]);
    }
    return unaryFunctionExprs[functionIndex];
}


/***************************************************
 ***************** Multi Functions *****************
 ***************************************************/

const MultiFunction multiFunctions[numFunctions] = {
    nullptr, f_absdev, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, f_argmax, f_argmin, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_autocorr, f_beta,
	f_betainc, f_choose, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, f_deriv, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_fcmp,
	nullptr, nullptr, nullptr, f_gammainc, f_gammaincp, f_gammaincq, nullptr, nullptr,
	f_hypot, nullptr, f_integral, nullptr, f_kurt, f_kurtosis, f_lag1, f_ldexp, nullptr,
	nullptr, nullptr, f_lnbeta, f_lnchoose, nullptr, nullptr, nullptr, f_lnpermute,
	f_lnpoch, nullptr, nullptr, nullptr, f_logn, f_max, f_mean, f_median, f_min, nullptr,
	f_permute, f_poch, f_pochrel, nullptr, nullptr, f_sd, nullptr, nullptr, nullptr,
	nullptr, f_skew, nullptr, f_std, f_stdev, nullptr, nullptr, f_taylorcoeff, f_tss, f_var,
	f_variance
};

MultiFunction get_multi_function(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Multi Function: ", name);
    }
    return get_multi_function(index);
}
MultiFunction get_multi_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] < 1 && functionNumArgs[functionIndex] != -1){
        throw Exception("Function is not Multi Arg: ", functionNames[functionIndex]);
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
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, fe_cubic,
	fe_cubicc, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, fe_fft, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	fe_ifft, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, fe_quad, fe_quadc, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

MultiFunctionExpr get_multi_function_expr(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Multi Function: ", name);
    }
    return get_multi_function_expr(index);
}
MultiFunctionExpr get_multi_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] < 1 && functionNumArgs[functionIndex] != -1){
        throw Exception("Function is not Multi Arg: ", functionNames[functionIndex]);
    }
    return multiFunctionExprs[functionIndex];
}
