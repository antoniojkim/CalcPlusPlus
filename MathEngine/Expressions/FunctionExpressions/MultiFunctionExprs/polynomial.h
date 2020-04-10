#pragma once

#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_poly.h>

#include "../../Expression.h"
#include "../../TupleExpression.h"

using namespace std;

inline expression make_tuple(initializer_list<double> vals){
    return make_unique<TupleExpression>(std::forward<initializer_list<double>>(vals));
}


expression fe_quad(list<expression>& args, const Variables& vars){
    auto arg = args.begin();
    double a = (*(arg++))->value(vars);
    double b = (*(arg++))->value(vars);
    double c = (*(arg++))->value(vars);
    double x0, x1;
    int num_roots = gsl_poly_solve_quadratic(a, b, c, &x0, &x1);
    switch(num_roots){
        case 0:
            return make_unique<TupleExpression>();
        case 1:
            return make_tuple({x0});
        case 2:
            return make_tuple({x0, x1});
        default:
            throw; // Should never throw;
    }
}

expression fe_cubic(list<expression>& args, const Variables& vars){
    auto arg = args.begin();
    double a = (*(arg++))->value(vars);
    double b = (*(arg++))->value(vars) / a;
    double c = (*(arg++))->value(vars) / a;
    double d = (*(arg++))->value(vars) / a;
    double x0, x1, x2;
    int num_roots = gsl_poly_solve_cubic(b, c, d, &x0, &x1, &x2);
    switch(num_roots){
        case 1:
            return make_tuple({x0});
        case 3:
            return make_tuple({x0, x1, x2});
        default:
            throw; // Should never throw;
    }
}
