#pragma once

#include <initializer_list>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Expression.h"
#include "../../TupleExpression.h"
#include "../FunctionDirectory.h"

expression fe_frexp(expression& arg, const Variables& vars){
    double x = arg->value(vars);
    int e;
    double f = gsl_frexp(x, &e);
    return std::make_unique<TupleExpression>(std::initializer_list<double>{f, (double) e});
}
