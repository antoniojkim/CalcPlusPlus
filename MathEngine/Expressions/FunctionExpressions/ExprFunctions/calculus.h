#pragma once

#include <list>
#include <cmath>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "../../../Utils/exceptions.h"
#include "../../Expression.h"
#include "../../InvalidExpression.h"
#include "../../VariableExpression.h"
#include "../FunctionDirectory.h"

expression fe_diff(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple){
        if (tuple->size() == 1){
            return tuple->front()->derivative("x");
        }
        if (tuple->size() == 2 && tuple->back()->variable()){
            auto var = tuple->back()->variable()->getName();
            return tuple->front()->derivative(var);
        }
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for differentiation"));
}
