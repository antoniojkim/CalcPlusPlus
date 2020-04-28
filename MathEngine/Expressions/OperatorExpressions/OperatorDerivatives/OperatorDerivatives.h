#pragma once

#include "../../ExpressionFunctions.h"
#include "../../ExpressionOperations.h"
#include "../BinaryOperatorDirectory.h"

expression fprime_PLUS(const expression lhs, const expression rhs, const std::string& var){
    return lhs->derivative(var) + rhs->derivative(var);
}

expression fprime_MINUS(const expression lhs, const expression rhs, const std::string& var){
    return lhs->derivative(var) - rhs->derivative(var);
}

expression fprime_STAR(const expression lhs, const expression rhs, const std::string& var){
    return lhs->derivative(var) * rhs + rhs->derivative(var) * lhs;
}

expression fprime_SLASH(const expression lhs, const expression rhs, const std::string& var){
    return (lhs->derivative(var) * rhs - rhs->derivative(var) * lhs) / (rhs ^ 2);
}

expression fprime_CARET(const expression lhs, const expression rhs, const std::string& var){
    if (rhs->evaluable()){
        return (lhs ^ (rhs - 1)) * (lhs->derivative(var) * rhs);
    }
    else if (lhs->evaluable()){
        return (lhs ^ rhs) *  ln(lhs) * rhs->derivative(var);
    }
    else{
        return (lhs ^ (rhs - 1)) * (lhs->derivative(var) * rhs + lhs * ln(lhs) * rhs->derivative(var));
    }
}

BinaryOperatorDerivative fprime_STAR_STAR = fprime_CARET;
