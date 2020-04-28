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
    return lhs->derivative(var) * rhs->copy() + rhs->derivative(var) * lhs->copy();
}

expression fprime_SLASH(const expression lhs, const expression rhs, const std::string& var){
    return (lhs->derivative(var) * rhs->copy() - rhs->derivative(var) * lhs->copy()) / (rhs->copy() ^ 2);
}

expression fprime_CARET(const expression lhs, const expression rhs, const std::string& var){
    if (rhs->evaluable()){
        return (lhs->copy() ^ (rhs->copy() - 1)) * (lhs->derivative(var) * rhs->copy());
    }
    else{
        return (lhs->copy() ^ (rhs->copy() - 1)) * (lhs->derivative(var) * rhs->copy() + lhs->copy() * ln(lhs->copy()) * rhs->derivative(var));
    }
}

BinaryOperatorDerivative fprime_STAR_STAR = fprime_CARET;
