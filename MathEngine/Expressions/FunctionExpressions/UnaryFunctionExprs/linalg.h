#pragma once

#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

#include "../../Expression.h"
#include "../../InvalidExpression.h"
#include "../../MatrixExpression.h"
#include "../../NumericalExpression.h"

using namespace std;

expression fe_det(expression& arg, const Variables& vars){
    if (arg->matrix()){
        auto matrix = arg->evaluate(vars);
        if (matrix->isComplex()){
            auto gsl_mat = matrix->matrix()->to_gsl_matrix_complex();
            auto gsl_perm = matrix->matrix()->to_gsl_permutation();
            int signum;
            gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
            return make_unique<NumExpression>(
                gsl_linalg_complex_LU_det(gsl_mat.get(), signum)
            );
        }
        else{
            auto gsl_mat = matrix->matrix()->to_gsl_matrix();
            auto gsl_perm = matrix->matrix()->to_gsl_permutation();
            int signum;
            gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
            return make_unique<NumExpression>(
                gsl_linalg_LU_det(gsl_mat.get(), signum)
            );
        }
    }
    return make_unique<InvalidExpression>(Exception("Determinant expects a matrix expression"));
}
