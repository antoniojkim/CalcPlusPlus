#pragma once

#include "../../ExpressionFunctions.h"
#include "../../ExpressionOperations.h"
#include "../BinaryOperatorDirectory.h"

expression fprime_PLUS(expression& lhs, expression& rhs, const std::string& var){
    return lhs->derivative(var) + rhs->derivative(var);
}

expression fprime_MINUS(expression& lhs, expression& rhs, const std::string& var){
    return lhs->derivative(var) - rhs->derivative(var);
}

expression fprime_STAR(expression& lhs, expression& rhs, const std::string& var){
    return lhs->derivative(var) * rhs->copy() + rhs->derivative(var) * lhs->copy();
}

expression fprime_SLASH(expression& lhs, expression& rhs, const std::string& var){
    return (lhs->derivative(var) * rhs->copy() - rhs->derivative(var) * lhs->copy()) / (rhs->copy() ^ 2);
}

expression fprime_CARET(expression& lhs, expression& rhs, const std::string& var){
    if (rhs->evaluable()){
        return (lhs->copy() ^ (rhs->copy() - 1)) * (lhs->derivative(var) * rhs->copy());
    }
    else{
        return (lhs->copy() ^ (rhs->copy() - 1)) * (lhs->derivative(var) * rhs->copy() + lhs->copy() * ln(lhs->copy()) * rhs->derivative(var));
    }
}

BinaryOperatorDerivative fprime_STAR_STAR = fprime_CARET;
