
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "Functions.h"
#include "../Utils/Exception.h"

using namespace Function;

namespace Functions {

	FunctionConstructor functionConstructors[Functions::numFunctions] = {
		make_fe_mod, make_fe_bitwise_and, make_fe_mul, make_fe_pow, make_fe_add, make_fe_sub,
		make_fe_div, make_fe_floordiv, make_fe_eq, make_fe_eq, make_fe_lshift, make_fe_eq,
		make_fe_rshift, make_fe_Beta, make_fe_Betainc, make_fe_choose, make_fe_Cholesky,
		make_fe_Cholesky, make_fe_Eig, make_fe_LU, make_fe_LUsolve, make_fe_permute, make_fe_QR,
		make_fe_SVD, make_fe_pow, make_fe_bitwise_xor, make_fe_abs, make_fe_absdev,
		make_fe_acos, make_fe_acosh, make_fe_acot, make_fe_acoth, make_fe_acsc, make_fe_acsch,
		make_fe_add, make_fe_acos, make_fe_acosh, make_fe_acot, make_fe_acoth, make_fe_acsc,
		make_fe_acsch, make_fe_acos, make_fe_acosh, make_fe_acot, make_fe_acoth, make_fe_acsc,
		make_fe_acsch, make_fe_asec, make_fe_asech, make_fe_asin, make_fe_asinh, make_fe_atan,
		make_fe_atanh, make_fe_argmax, make_fe_argmin, make_fe_asec, make_fe_asech,
		make_fe_asin, make_fe_asinh, make_fe_atan, make_fe_atanh, make_fe_asec, make_fe_asech,
		make_fe_asin, make_fe_asinh, make_fe_atan, make_fe_atanh, make_fe_lag1, make_fe_bin,
		make_fe_bitwise_and, make_fe_bitwise_or, make_fe_bitwise_xor, make_fe_cb, make_fe_cbrt,
		make_fe_Cholesky, make_fe_choose, make_fe_choose, make_fe_cos, make_fe_cosh,
		make_fe_cot, make_fe_coth, make_fe_csc, make_fe_csch, make_fe_cubic, make_fe_cubicc,
		make_fe_deg, make_fe_deriv, make_fe_det, make_fe_dfact, make_fe_diff, make_fe_div,
		make_fe_Eig, make_fe_Eig, make_fe_eq, make_fe_exp, make_fe_exp2, make_fe_expm1,
		make_fe_fact, make_fe_fcmp, make_fe_fft, make_fe_floordiv, make_fe_frexp, make_fe_gamma,
		make_fe_gamma_inc, make_fe_gamma_inc_P, make_fe_gamma_inc_Q, make_fe_gamma_inc,
		make_fe_gamma_inc_P, make_fe_gamma_inc_Q, make_fe_gammainv, make_fe_gammastar,
		make_fe_gcd, make_fe_hex, make_fe_hypot, make_fe_ifft, make_fe_integral,
		make_fe_kurtosis, make_fe_kurtosis, make_fe_lag1, make_fe_lcm, make_fe_ldexp,
		make_fe_ln, make_fe_ln1p, make_fe_ln2, make_fe_lnBeta, make_fe_lnchoose,
		make_fe_lnchoose, make_fe_lndet, make_fe_lndfact, make_fe_lnfact, make_fe_lngamma,
		make_fe_lnpermute, make_fe_lnpermute, make_fe_lnpoch, make_fe_log, make_fe_log,
		make_fe_ln1p, make_fe_log1pm, make_fe_ln2, make_fe_logabs, make_fe_logn, make_fe_lshift,
		make_fe_max, make_fe_argmax, make_fe_mean, make_fe_median, make_fe_min, make_fe_argmin,
		make_fe_mod, make_fe_mul, make_fe_neg, make_fe_num, make_fe_permute, make_fe_permute,
		make_fe_poch, make_fe_pochrel, make_fe_pow, make_fe_quad, make_fe_quadc, make_fe_rad,
		make_fe_rand, make_fe_rshift, make_fe_sd, make_fe_sec, make_fe_sech, make_fe_sin,
		make_fe_sinh, make_fe_skew, make_fe_LUsolve, make_fe_sqr, make_fe_sqrt, make_fe_sd,
		make_fe_sd, make_fe_sub, make_fe_tan, make_fe_tanh, make_fe_taylorcoeff, make_fe_tss,
		make_fe_var, make_fe_var, make_fe_bitwise_or
	};

	expression construct(const int functionIndex, const expression arg){
		if (functionIndex < 0){
			throw Exception("Invalid Function Index: ", functionIndex);
		}
		return functionConstructors[functionIndex](functionIndex, arg);
	}

	bool functionIsOperator[Functions::numFunctions] = {
		true, true, true, true, true, true, true, true, true, true, true, true, true, false,
		false, false, false, false, false, false, false, false, false, false, true, true, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, true
	};

	bool isOperator(const char* name){
		return functionIsOperator[Functions::indexOf(name)];
	}
	bool isOperator(const int functionIndex){
		if (functionIndex < 0){
			throw Exception("Invalid Function Index: ", functionIndex);
		}
		return functionIsOperator[functionIndex];
	}
}
