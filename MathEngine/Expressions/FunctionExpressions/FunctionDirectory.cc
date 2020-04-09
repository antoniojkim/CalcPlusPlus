
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "Functions.h"
#include "MultiFunctions/Calculus.h"
#include "MultiFunctions/ExpLogFunctions.h"
#include "MultiFunctions/Statistics.h"
#include "UnaryFunctions/ExpLogFunctions.h"
#include "UnaryFunctions/TrigFunctions.h"

using namespace std;

/***************************************************
 ***************** Unary Functions *****************
 ***************************************************/

const UnaryFunction unaryFunctions[numFunctions] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, f_arctanh, f_arcsinh, f_arcsech,
	f_arccsch, f_arccoth, f_arccosh, nullptr, f_artanh, f_arsinh, f_arsech, nullptr,
	nullptr, f_arctan, f_arcsin, f_arcsec, f_arcsch, f_arcoth, f_arcosh, f_arccsc,
	f_arccot, f_arccos, nullptr, nullptr, f_log_2, f_log1p, f_expm1, f_exp_2,
	nullptr, f_atanh, f_asinh, f_asech, f_acsch, f_acoth, f_acosh, f_tanh, nullptr,
	f_sinh, f_sech, nullptr, nullptr, f_ln_2, f_ln1p, nullptr, nullptr, f_csch,
	f_coth, f_cosh, f_atan, f_asin, f_asec, f_acsc, f_acot, f_acos, nullptr,
	nullptr, f_tan, nullptr, f_sin, f_sec, nullptr, nullptr, f_log, f_exp, f_csc,
	f_cot, f_cos, nullptr, f_ln, nullptr
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
 ***************** Multi Functions *****************
 ***************************************************/

const MultiFunction multiFunctions[numFunctions] = {
    nullptr, f_variance, f_kurtosis, nullptr, f_autocorr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, f_median, nullptr, nullptr, nullptr, f_argmin,
	f_argmax, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, f_absdev, f_stdev, nullptr, nullptr, nullptr, nullptr,
	f_deriv, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_skew,
	nullptr, nullptr, f_mean, f_logn, nullptr, nullptr, f_lag1, f_kurt, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_var,
	f_tss, nullptr, f_std, nullptr, nullptr, f_min, f_max, nullptr, nullptr,
	nullptr, nullptr, nullptr, f_sd, nullptr, nullptr
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