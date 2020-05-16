#pragma once

#include <cmath>

#include "../FunctionDirectory.h"
#include "../../FunctionExpression.h"
#include "../../ExpressionOperations.h"
#include "../../ExpressionFunctions.h"


expression fprime_sin(const expression arg, const std::string& var){
    return FunctionExpression::construct("cos", arg);
}
expression fprime_cos(const expression arg, const std::string& var){
    return -FunctionExpression::construct("sin", arg);
}
expression fprime_tan(const expression arg, const std::string& var){
    return FunctionExpression::construct("sec", arg) ^ 2;
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
DerivativeFunction fprime_arcsin = fprime_asin;
DerivativeFunction fprime_arccos = fprime_acos;
DerivativeFunction fprime_arctan = fprime_atan;

expression fprime_sinh(const expression arg, const std::string& var){
    return FunctionExpression::construct("cosh", arg);
}
expression fprime_cosh(const expression arg, const std::string& var){
    return FunctionExpression::construct("sinh", arg);
}
expression fprime_tanh(const expression arg, const std::string& var){
    return FunctionExpression::construct("sech", arg) ^ 2;
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
DerivativeFunction fprime_arcsinh = fprime_asinh;
DerivativeFunction fprime_arccosh = fprime_acosh;
DerivativeFunction fprime_arctanh = fprime_atanh;
DerivativeFunction fprime_arsinh = fprime_asinh;
DerivativeFunction fprime_arcosh = fprime_acosh;
DerivativeFunction fprime_artanh = fprime_atanh;

expression fprime_csc(const expression arg, const std::string& var){
    return -FunctionExpression::construct("cot", arg) * FunctionExpression::construct("csc", arg);
}
expression fprime_sec(const expression arg, const std::string& var){
    return -FunctionExpression::construct("tan", arg) * FunctionExpression::construct("sec", arg);
}
expression fprime_cot(const expression arg, const std::string& var){
    return -(FunctionExpression::construct("csc", arg) ^ 2);
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
DerivativeFunction fprime_arcsc = fprime_acsc;
DerivativeFunction fprime_arsec = fprime_asec;
DerivativeFunction fprime_arcot = fprime_acot;
DerivativeFunction fprime_arccsc = fprime_acsc;
DerivativeFunction fprime_arcsec = fprime_asec;
DerivativeFunction fprime_arccot = fprime_acot;

expression fprime_csch(const expression arg, const std::string& var){
    return -FunctionExpression::construct("coth", arg) * FunctionExpression::construct("csch", arg);
}
expression fprime_sech(const expression arg, const std::string& var){
    return -FunctionExpression::construct("tanh", arg) * FunctionExpression::construct("sech", arg);
}
expression fprime_coth(const expression arg, const std::string& var){
    return -(FunctionExpression::construct("csch", arg) ^ 2);
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
DerivativeFunction fprime_arcsch = fprime_acsch;
DerivativeFunction fprime_arsech = fprime_asech;
DerivativeFunction fprime_arcoth = fprime_acoth;
DerivativeFunction fprime_arccsch = fprime_acsch;
DerivativeFunction fprime_arcsech = fprime_asech;
DerivativeFunction fprime_arccoth = fprime_acoth;
