
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "UnaryFunctionDirectory.h"
#include "UnaryFunctions/TrigFunctions.h"
#include "UnaryFunctions/ExpLogFunctions.h"

using namespace std;

const UnaryFunction unaryFunctions[numFunctions] = {
    nullptr, nullptr, f_arctanh, f_arcsinh, f_arcsech, f_arccsch, f_arccoth,
	f_arccosh, f_artanh, f_arsinh, f_arsech, f_arctan, f_arcsin, f_arcsec, f_arcsch,
	f_arcoth, f_arcosh, f_arccsc, f_arccot, f_arccos, f_log1p, f_expm1, nullptr,
	f_atanh, f_asinh, f_asech, f_acsch, f_acoth, f_acosh, f_tanh, f_sinh, f_sech,
	nullptr, f_log2, f_ln1p, f_exp2, f_csch, f_coth, f_cosh, f_atan, f_asin, f_asec,
	f_acsc, f_acot, f_acos, f_tan, f_sin, f_sec, f_log, f_ln2, f_exp, f_csc, f_cot,
	f_cos, f_ln, nullptr
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