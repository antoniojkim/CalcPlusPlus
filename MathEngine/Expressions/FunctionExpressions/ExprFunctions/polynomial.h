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

expression fe_quad(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 3){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*(arg++))->value(vars);
        double c = (*(arg++))->value(vars);
        double x0, x1;
        int num_roots = gsl_poly_solve_quadratic(a, b, c, &x0, &x1);
        switch(num_roots){
            case 0:
                return TupleExpression::construct();
            case 1:
                return TupleExpression::construct({x0});
            case 2:
                if (gsl_fcmp(x0, x1, 1e-15) == 0){
                    return TupleExpression::construct({x0});
                }
                return TupleExpression::construct({x0, x1});
            default:
                throw; // Should never throw;
        }
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for quad"));
}

expression fe_quadc(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 3){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*(arg++))->value(vars);
        double c = (*(arg++))->value(vars);
        gsl_complex z0, z1;
        int num_roots = gsl_poly_complex_solve_quadratic(a, b, c, &z0, &z1);
        switch(num_roots){
            case 0:
                return TupleExpression::construct();
            case 1:
                return TupleExpression::construct({z0});
            case 2:
                return TupleExpression::construct({z0, z1});
            default:
                throw; // Should never throw;
        }
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for quadc"));
}

expression fe_cubic(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 4){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*(arg++))->value(vars) / a;
        double c = (*(arg++))->value(vars) / a;
        double d = (*(arg++))->value(vars) / a;
        double x0, x1, x2;
        int num_roots = gsl_poly_solve_cubic(b, c, d, &x0, &x1, &x2);
        switch(num_roots){
            case 1:
                return TupleExpression::construct({x0});
            case 3:
                return TupleExpression::construct({x0, x1, x2});
            default:
                throw; // Should never throw;
        }
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for cubic"));
}

expression fe_cubicc(expression arg, const Variables& vars){
    TupleExpression* tuple = arg->tuple();
    if (tuple && tuple->size() == 4){
        auto arg = tuple->begin();
        double a = (*(arg++))->value(vars);
        double b = (*(arg++))->value(vars) / a;
        double c = (*(arg++))->value(vars) / a;
        double d = (*(arg++))->value(vars) / a;
        gsl_complex z0, z1, z2;
        gsl_poly_complex_solve_cubic(b, c, d, &z0, &z1, &z2);
        return TupleExpression::construct({z0, z1, z2});
    }
    return InvalidExpression::construct(Exception("Invalid number of arguments for cubicc"));
}
