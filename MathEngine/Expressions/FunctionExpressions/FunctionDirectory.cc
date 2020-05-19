
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "Functions.h"
#include "ExprFunctions/basic.h"
#include "ExprFunctions/calculus.h"
#include "ExprFunctions/fft.h"
#include "ExprFunctions/linalg.h"
#include "ExprFunctions/polynomial.h"
#include "ValueFunctions/BasicFunctions.h"
#include "ValueFunctions/Calculus.h"
#include "ValueFunctions/ExpLogFunctions.h"
#include "ValueFunctions/Random.h"
#include "ValueFunctions/SpecialFunctions.h"
#include "ValueFunctions/Statistics.h"
#include "ValueFunctions/TrigFunctions.h"
#include "DerivativeFunctions/BasicFunctions.h"
#include "DerivativeFunctions/ExpLogFunctions.h"
#include "DerivativeFunctions/TrigFunctions.h"

using namespace std;
using Function::numFunctions;

/***************************************************
 ***************** Unary Functions *****************
 ***************************************************/

const ValueFunction valueFunctions[numFunctions] = {
    nullptr, nullptr, f_abs, f_absdev, f_acos, f_acosh, f_acot, f_acoth, f_acsc, f_acsch,
	f_arccos, f_arccosh, f_arccot, f_arccoth, f_arccsc, f_arccsch, f_arcosh, f_arcoth,
	f_arcsch, f_arcsec, f_arcsech, f_arcsin, f_arcsinh, f_arctan, f_arctanh, f_argmax,
	f_argmin, f_arsech, f_arsinh, f_artanh, f_asec, f_asech, f_asin, f_asinh, f_atan,
	f_atanh, f_autocorr, f_beta, f_betainc, nullptr, f_cb, f_cbrt, f_choose, f_cos, f_cosh,
	f_cot, f_coth, f_csc, f_csch, nullptr, nullptr, f_deg, f_deriv, nullptr, f_dfact,
	nullptr, f_exp, f_exp_2, f_expm1, f_fact, f_fcmp, nullptr, nullptr, f_gamma, f_gammainc,
	f_gammaincp, f_gammaincq, f_gammainv, f_gammastar, f_gcd, nullptr, f_hypot, nullptr,
	f_integral, f_kurt, f_kurtosis, f_lag1, f_lcm, f_ldexp, f_ln, f_ln1p, f_ln_2, f_lnbeta,
	f_lnchoose, f_lndfact, f_lnfact, f_lngamma, f_lnpermute, f_lnpoch, f_log, f_log1p,
	f_log_2, f_logn, f_max, f_mean, f_median, f_min, nullptr, nullptr, f_permute, f_poch,
	f_pochrel, nullptr, nullptr, f_rad, f_rand, f_randint, f_randseed, f_randu, f_randup,
	f_rseed, f_sd, f_sec, f_sech, f_sin, f_sinh, f_skew, f_sqr, f_sqrt, f_std, f_stdev,
	f_tan, f_tanh, f_taylorcoeff, f_tss, f_var, f_variance
};

ValueFunction get_function(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Function: ", name);
    }
    return get_function(index);
}
ValueFunction get_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    return valueFunctions[functionIndex];
}


/***************************************************
 ***************** Expr Functions ******************
 ***************************************************/

const ExprFunction exprFunctions[numFunctions] = {
    fe_Cholesky, fe_LU, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fe_bin, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fe_cubic, fe_cubicc, nullptr, nullptr, fe_det, nullptr,
	fe_diff, nullptr, nullptr, nullptr, nullptr, nullptr, fe_fft, fe_frexp, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, fe_hex, nullptr, fe_ifft, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, fe_neg, fe_num, nullptr, nullptr, nullptr,
	fe_quad, fe_quadc, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};

ExprFunction get_function_expr(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_function_expr(index);
}
ExprFunction get_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    return exprFunctions[functionIndex];
}


/***************************************************
 ************** Function Derivatives ***************
 ***************************************************/

const DerivativeFunction derivativeFunctions[numFunctions] = {
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
	fprime_logn, nullptr, nullptr, nullptr, nullptr, fprime_neg, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, fprime_sec, fprime_sech, fprime_sin, fprime_sinh, nullptr, fprime_sqr,
	fprime_sqrt, nullptr, nullptr, fprime_tan, fprime_tanh, nullptr, nullptr, nullptr,
	nullptr
};

DerivativeFunction get_function_derivative(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Function: ", name);
    }
    return get_function_derivative(index);
}
DerivativeFunction get_function_derivative(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    return derivativeFunctions[functionIndex];
}
