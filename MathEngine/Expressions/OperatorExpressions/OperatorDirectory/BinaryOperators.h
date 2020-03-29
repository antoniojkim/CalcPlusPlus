#pragma once

#include <cmath>
#include <gsl/gsl_math.h>

#include "../BinaryOperatorDirectory.h"


double f_PLUS(double lhs, double rhs){ return lhs + rhs; };
double f_MINUS(double lhs, double rhs){ return lhs - rhs; };
double f_STAR(double lhs, double rhs){ return lhs * rhs; };
double f_SLASH(double lhs, double rhs){ return lhs / rhs; };
BinaryOperator f_PCT = std::fmod;
double f_SLASH_SLASH(double lhs, double rhs){
    double intpart;
    modf(lhs / rhs, &intpart);
    return intpart;
}
BinaryOperator f_CARET = std::pow;
BinaryOperator f_STAR_STAR = std::pow;
double f_LT_LT(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return ((long long int) intpartl) << ((long long int) intpartr);
    }
    return GSL_NAN;
}
double f_GT_GT(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return double(((long long int) intpartl) >> ((long long int) intpartr));
    }
    return GSL_NAN;
}
double f_AMP(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return double(((long long int) intpartl) & ((long long int) intpartr));
    }
    return GSL_NAN;
}
double f_PIPE(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return double(((long long int) intpartl) | ((long long int) intpartr));
    }
    return GSL_NAN;
}
double f_AMP_AMP(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return double(((long long int) intpartl) && ((long long int) intpartr));
    }
    return GSL_NAN;
}
double f_PIPE_PIPE(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return double(((long long int) intpartl) || ((long long int) intpartr));
    }
    return GSL_NAN;
}
double f_CARET_PIPE(double lhs, double rhs){
    double intpartl, intpartr;
    if (modf(lhs, &intpartl) == 0 && modf(rhs, &intpartr) == 0){
        return double(((long long int) intpartl) ^ ((long long int) intpartr));
    }
    return GSL_NAN;
}

BinaryOperator f_COMMA = nullptr;
BinaryOperator f_EQUALS = nullptr;
BinaryOperator f_COLON_EQUALS = nullptr;
BinaryOperator f_L_ARROW = nullptr;
BinaryOperator f_EQUALS_EQUALS = nullptr;
BinaryOperator f_NOT_EQUALS = nullptr;
BinaryOperator f_LT = nullptr;
BinaryOperator f_GT = nullptr;
BinaryOperator f_LT_EQ = nullptr;
BinaryOperator f_GT_EQ = nullptr;
BinaryOperator f_COLON = nullptr;
BinaryOperator f_R_ARROW = nullptr;
