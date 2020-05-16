#pragma once

#include <cmath>

#include "../FunctionDirectory.h"


ValueFunction f_sin = valueFunction<std::sin>;
ValueFunction f_cos = valueFunction<std::cos>;
ValueFunction f_tan = valueFunction<std::tan>;
ValueFunction f_asin = valueFunction<std::asin>;
ValueFunction f_acos = valueFunction<std::acos>;
ValueFunction f_atan = valueFunction<std::atan>;
ValueFunction f_arcsin = valueFunction<std::asin>;
ValueFunction f_arccos = valueFunction<std::acos>;
ValueFunction f_arctan = valueFunction<std::atan>;
ValueFunction f_sinh = valueFunction<std::sinh>;
ValueFunction f_cosh = valueFunction<std::cosh>;
ValueFunction f_tanh = valueFunction<std::tanh>;
ValueFunction f_asinh = valueFunction<std::asinh>;
ValueFunction f_acosh = valueFunction<std::acosh>;
ValueFunction f_atanh = valueFunction<std::atanh>;
ValueFunction f_arsinh = valueFunction<std::asinh>;
ValueFunction f_arcosh = valueFunction<std::acosh>;
ValueFunction f_artanh = valueFunction<std::atanh>;
ValueFunction f_arcsinh = valueFunction<std::asinh>;
ValueFunction f_arccosh = valueFunction<std::acosh>;
ValueFunction f_arctanh = valueFunction<std::atanh>;

double csc(double x){ return 1.0 / std::sin(x); }
double sec(double x){ return 1.0 / std::cos(x); }
double cot(double x){ return 1.0 / std::tan(x); }
ValueFunction f_csc = valueFunction<csc>;
ValueFunction f_sec = valueFunction<sec>;
ValueFunction f_cot = valueFunction<cot>;

double acsc(double x){ return std::asin(1.0 / x); }
double asec(double x){ return std::acos(1.0 / x); }
double acot(double x){ return std::tan(1.0 / x); }
ValueFunction f_acsc = valueFunction<acsc>;
ValueFunction f_asec = valueFunction<asec>;
ValueFunction f_acot = valueFunction<acot>;
ValueFunction f_arcsc = valueFunction<acsc>;
ValueFunction f_arsec = valueFunction<asec>;
ValueFunction f_arcot = valueFunction<acot>;
ValueFunction f_arccsc = valueFunction<acsc>;
ValueFunction f_arcsec = valueFunction<asec>;
ValueFunction f_arccot = valueFunction<acot>;

double csch(double x){ return 1.0 / std::sinh(x); }
double sech(double x){ return 1.0 / std::cosh(x); }
double coth(double x){ return 1.0 / std::tanh(x); }
ValueFunction f_csch = valueFunction<csch>;
ValueFunction f_sech = valueFunction<sech>;
ValueFunction f_coth = valueFunction<coth>;

double acsch(double x){ return std::asinh(1.0 / x); }
double asech(double x){ return std::acosh(1.0 / x); }
double acoth(double x){ return std::tanh(1.0 / x); }
ValueFunction f_acsch = valueFunction<acsch>;
ValueFunction f_asech = valueFunction<asech>;
ValueFunction f_acoth = valueFunction<acoth>;
ValueFunction f_arcsch = valueFunction<acsch>;
ValueFunction f_arsech = valueFunction<asech>;
ValueFunction f_arcoth = valueFunction<acoth>;
ValueFunction f_arccsch = valueFunction<acsch>;
ValueFunction f_arcsech = valueFunction<asech>;
ValueFunction f_arccoth = valueFunction<acoth>;
