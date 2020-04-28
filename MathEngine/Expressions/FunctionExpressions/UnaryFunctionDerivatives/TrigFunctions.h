#pragma once

#include <cmath>

#include "../FunctionDirectory.h"
#include "../../FunctionExpression.h"
#include "../../ExpressionOperations.h"
#include "../../ExpressionFunctions.h"


expression fprime_sin(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("cos", arg);
}
expression fprime_cos(const expression arg, const std::string& var){
    return -UnaryFunctionExpression::construct("sin", arg);
}
expression fprime_tan(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("sec", arg) ^ 2;
}

expression fprime_asin(const expression arg, const std::string& var){
    return 1 / sqrt(1 - (arg ^ 2));
}
expression fprime_acos(const expression arg, const std::string& var){
    return -1 / sqrt(1 - (arg ^ 2));
}
expression fprime_atan(const expression arg, const std::string& var){
    return 1 / (1 + (arg ^ 2));
}
UnaryFunctionDerivative fprime_arcsin = fprime_asin;
UnaryFunctionDerivative fprime_arccos = fprime_acos;
UnaryFunctionDerivative fprime_arctan = fprime_atan;

expression fprime_sinh(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("cosh", arg);
}
expression fprime_cosh(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("sinh", arg);
}
expression fprime_tanh(const expression arg, const std::string& var){
    return UnaryFunctionExpression::construct("sech", arg) ^ 2;
}
expression fprime_asinh(const expression arg, const std::string& var){
    return 1 / sqrt((arg ^ 2) + 1);
}
expression fprime_acosh(const expression arg, const std::string& var){
    return 1 / sqrt((arg ^ 2) - 1);
}
expression fprime_atanh(const expression arg, const std::string& var){
    return 1 / (1 - (arg ^ 2));
}
UnaryFunctionDerivative fprime_arcsinh = fprime_asinh;
UnaryFunctionDerivative fprime_arccosh = fprime_acosh;
UnaryFunctionDerivative fprime_arctanh = fprime_atanh;
UnaryFunctionDerivative fprime_arsinh = fprime_asinh;
UnaryFunctionDerivative fprime_arcosh = fprime_acosh;
UnaryFunctionDerivative fprime_artanh = fprime_atanh;

expression fprime_csc(const expression arg, const std::string& var){
    return -UnaryFunctionExpression::construct("cot", arg) * UnaryFunctionExpression::construct("csc", arg);
}
expression fprime_sec(const expression arg, const std::string& var){
    return -UnaryFunctionExpression::construct("tan", arg) * UnaryFunctionExpression::construct("sec", arg);
}
expression fprime_cot(const expression arg, const std::string& var){
    return -(UnaryFunctionExpression::construct("csc", arg) ^ 2);
}
expression fprime_acsc(const expression arg, const std::string& var){
    return -1 / (abs(arg) * sqrt((arg ^ 2) - 1));
}
expression fprime_asec(const expression arg, const std::string& var){
    return 1 / (abs(arg) * sqrt((arg ^ 2) - 1));
}
expression fprime_acot(const expression arg, const std::string& var){
    return -1 / (1 + (arg ^ 2));
}
UnaryFunctionDerivative fprime_arcsc = fprime_acsc;
UnaryFunctionDerivative fprime_arsec = fprime_asec;
UnaryFunctionDerivative fprime_arcot = fprime_acot;
UnaryFunctionDerivative fprime_arccsc = fprime_acsc;
UnaryFunctionDerivative fprime_arcsec = fprime_asec;
UnaryFunctionDerivative fprime_arccot = fprime_acot;

expression fprime_csch(const expression arg, const std::string& var){
    return -UnaryFunctionExpression::construct("coth", arg) * UnaryFunctionExpression::construct("csch", arg);
}
expression fprime_sech(const expression arg, const std::string& var){
    return -UnaryFunctionExpression::construct("tanh", arg) * UnaryFunctionExpression::construct("sech", arg);
}
expression fprime_coth(const expression arg, const std::string& var){
    return -(UnaryFunctionExpression::construct("csch", arg) ^ 2);
}
expression fprime_acsch(const expression arg, const std::string& var){
    return -1 / (abs(arg) * sqrt((arg ^ 2) - 1));
}
expression fprime_asech(const expression arg, const std::string& var){
    return -1 / (abs(arg) * sqrt(1 - (arg ^ 2)));
}
expression fprime_acoth(const expression arg, const std::string& var){
    return 1 / (1 - (arg ^ 2));
}
UnaryFunctionDerivative fprime_arcsch = fprime_acsch;
UnaryFunctionDerivative fprime_arsech = fprime_asech;
UnaryFunctionDerivative fprime_arcoth = fprime_acoth;
UnaryFunctionDerivative fprime_arccsch = fprime_acsch;
UnaryFunctionDerivative fprime_arcsech = fprime_asech;
UnaryFunctionDerivative fprime_arccoth = fprime_acoth;
