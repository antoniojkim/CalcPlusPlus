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

expression fe_diff(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        return args.front()->derivative("x");
    }
    if (args.size() == 2 && args.back()->variable()){
        auto var = args.back()->variable()->getName();
        return args.front()->derivative(var);
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for differentiation: ", args.size()));
}
