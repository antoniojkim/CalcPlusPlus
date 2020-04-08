#pragma once

#include <cmath>

#include "../FunctionDirectory.h"


UnaryFunction f_sin = std::sin;
UnaryFunction f_cos = std::cos;
UnaryFunction f_tan = std::tan;
UnaryFunction f_asin = std::asin;
UnaryFunction f_acos = std::acos;
UnaryFunction f_atan = std::atan;
UnaryFunction f_arcsin = std::asin;
UnaryFunction f_arccos = std::acos;
UnaryFunction f_arctan = std::atan;
UnaryFunction f_sinh = std::sinh;
UnaryFunction f_cosh = std::cosh;
UnaryFunction f_tanh = std::tanh;
UnaryFunction f_asinh = std::asinh;
UnaryFunction f_acosh = std::acosh;
UnaryFunction f_atanh = std::atanh;
UnaryFunction f_arsinh = std::asinh;
UnaryFunction f_arcosh = std::acosh;
UnaryFunction f_artanh = std::atanh;
UnaryFunction f_arcsinh = std::asinh;
UnaryFunction f_arccosh = std::acosh;
UnaryFunction f_arctanh = std::atanh;

double f_csc(double x){ return 1.0 / std::sin(x); }
double f_sec(double x){ return 1.0 / std::cos(x); }
double f_cot(double x){ return 1.0 / std::tan(x); }
double f_acsc(double x){ return std::asin(1.0 / x); }
double f_asec(double x){ return std::acos(1.0 / x); }
double f_acot(double x){ return std::tan(1.0 / x); }
UnaryFunction f_arcsc = f_acsc;
UnaryFunction f_arsec = f_asec;
UnaryFunction f_arcot = f_acot;
UnaryFunction f_arccsc = f_acsc;
UnaryFunction f_arcsec = f_asec;
UnaryFunction f_arccot = f_acot;

double f_csch(double x){ return 1.0 / std::sinh(x); }
double f_sech(double x){ return 1.0 / std::cosh(x); }
double f_coth(double x){ return 1.0 / std::tanh(x); }
double f_acsch(double x){ return std::asinh(1.0 / x); }
double f_asech(double x){ return std::acosh(1.0 / x); }
double f_acoth(double x){ return std::tanh(1.0 / x); }
UnaryFunction f_arcsch = f_acsch;
UnaryFunction f_arsech = f_asech;
UnaryFunction f_arcoth = f_acoth;
UnaryFunction f_arccsch = f_acsch;
UnaryFunction f_arcsech = f_asech;
UnaryFunction f_arccoth = f_acoth;
