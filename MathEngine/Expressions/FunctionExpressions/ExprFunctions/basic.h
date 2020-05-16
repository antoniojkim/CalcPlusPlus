#pragma once

#include <initializer_list>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expression.h"
#include "../../InvalidExpression.h"
#include "../../NumericalExpression.h"
#include "../../TupleExpression.h"
#include "../FunctionDirectory.h"

expression fe_neg(expression arg, const Variables& vars){
    if (arg->isComplex()){
        return NumExpression::construct(gsl_complex_negative(arg->complex(vars)));
    }
    return NumExpression::construct(-arg->value(vars));
}

expression fe_frexp(expression arg, const Variables& vars){
    double x = arg->value(vars);
    int e;
    double f = gsl_frexp(x, &e);
    return TupleExpression::construct({f, (double) e});
}

expression fe_num(expression arg, const Variables& vars){
    return NumExpression::construct(arg->value(vars));
}
expression fe_hex(expression arg, const Variables& vars){
    if (!arg->isComplex()){
        double val = arg->value(vars);
        if (std::trunc(val) == val){
            return HexExpression::construct((unsigned long long) std::trunc(val));
        }
    }
    return InvalidExpression::construct(Exception("Unable to convert value to hex: ", arg));
}
expression fe_bin(expression arg, const Variables& vars){
    if (!arg->isComplex()){
        double val = arg->value(vars);
        if (std::trunc(val) == val){
            return BinExpression::construct((unsigned long long) std::trunc(val));
        }
    }
    return InvalidExpression::construct(Exception("Unable to convert value to bin: ", arg));
}
