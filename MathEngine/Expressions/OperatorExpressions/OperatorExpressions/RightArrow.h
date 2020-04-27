#pragma once

#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>

#include "../../InvalidExpression.h"
#include "../../NumericalExpression.h"
#include "../../MatrixExpression.h"
#include "../../UnitExpression.h"
#include "../BinaryOperatorDirectory.h"
#include "../OperatorDirectory/BinaryOperators.h"

inline expression unit_conversion(BaseUnitExpression* unit1, BaseUnitExpression* unit2){
    return convert(*unit1, *unit2);
}

expression fe_R_ARROW(expression& lhs, expression& rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->unit() && rexpr->unit()){
        return unit_conversion(lexpr->unit(), rexpr->unit());
    }
    return InvalidExpression::construct(Exception("Right Arrow requires both arguments to be unit expressions."));
}
