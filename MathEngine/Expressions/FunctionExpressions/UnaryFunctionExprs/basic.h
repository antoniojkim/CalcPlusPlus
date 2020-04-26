#pragma once

#include <initializer_list>
#include <memory>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expression.h"
#include "../../NumericalExpression.h"
#include "../../TupleExpression.h"
#include "../FunctionDirectory.h"

expression fe_neg(expression& arg, const Variables& vars){
    if (arg->isComplex()){
        return std::make_unique<NumExpression>(gsl_complex_negative(arg->complex(vars)));
    }
    return std::make_unique<NumExpression>(-arg->value(vars));
}

expression fe_frexp(expression& arg, const Variables& vars){
    double x = arg->value(vars);
    int e;
    double f = gsl_frexp(x, &e);
    return std::make_unique<TupleExpression>(std::initializer_list<double>{f, (double) e});
}
