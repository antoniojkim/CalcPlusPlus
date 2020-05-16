#pragma once

#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>

#include "../../InvalidExpression.h"
#include "../../NumericalExpression.h"
#include "../../MatrixExpression.h"
#include "../../UnitExpression.h"
#include "../OperatorDirectory.h"
#include "../Operators/BinaryOperators.h"

inline expression unit_conversion(const BaseUnitExpression* unit1, const BaseUnitExpression* unit2){
    return convert(*unit1, *unit2);
}

expression fe_R_ARROW(const expression lhs, const expression rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->unit() && rexpr->unit()){
        return unit_conversion(lexpr->unit(), rexpr->unit());
    }
    return InvalidExpression::construct(Exception("Right Arrow requires both arguments to be unit expressions."));
}
