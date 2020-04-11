#pragma once

#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>

#include "../../Expression.h"
#include "../../TupleExpression.h"

using namespace std;

inline expression make_tuple(initializer_list<double> vals){
    return make_unique<TupleExpression>(std::forward<initializer_list<double>>(vals));
}
inline expression make_tuple(initializer_list<gsl_complex> vals){
    return make_unique<TupleExpression>(std::forward<initializer_list<gsl_complex>>(vals));
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
            if (gsl_fcmp(x0, x1, 1e-15) == 0){
                return make_tuple({x0});
            }
            return make_tuple({x0, x1});
        default:
            throw; // Should never throw;
    }
}

expression fe_quadc(list<expression>& args, const Variables& vars){
    auto arg = args.begin();
    double a = (*(arg++))->value(vars);
    double b = (*(arg++))->value(vars);
    double c = (*(arg++))->value(vars);
    gsl_complex z0, z1;
    int num_roots = gsl_poly_complex_solve_quadratic(a, b, c, &z0, &z1);
    switch(num_roots){
        case 0:
            return make_unique<TupleExpression>();
        case 1:
            return make_tuple({z0});
        case 2:
            return make_tuple({z0, z1});
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

expression fe_cubicc(list<expression>& args, const Variables& vars){
    auto arg = args.begin();
    double a = (*(arg++))->value(vars);
    double b = (*(arg++))->value(vars) / a;
    double c = (*(arg++))->value(vars) / a;
    double d = (*(arg++))->value(vars) / a;
    gsl_complex z0, z1, z2;
    gsl_poly_complex_solve_cubic(b, c, d, &z0, &z1, &z2);
    return make_tuple({z0, z1, z2});
}
