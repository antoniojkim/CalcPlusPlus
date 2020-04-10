#pragma once

#include <list>
#include <vector>

#include <gsl/gsl_poly.h>

#include "../../Expression.h"
#include "../../TupleExpression.h"

using namespace std;


expression fe_tuple(list<expression>& args, const Variables& vars){
    list<expression> exprs;
    for (auto& arg : args){
        exprs.emplace_back(arg->evaluate(vars));
    }
    return make_unique<TupleExpression>(std::move(exprs));
}
