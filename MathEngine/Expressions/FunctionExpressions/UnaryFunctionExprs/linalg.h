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

typedef unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> unique_gsl_matrix;
typedef unique_ptr<gsl_matrix_complex, decltype(&gsl_matrix_complex_free)> unique_gsl_matrix_complex;
typedef unique_ptr<gsl_permutation, decltype(&gsl_permutation_free)> unique_gsl_permutation;

inline unique_gsl_matrix make_gsl_matrix(MatrixExpression* m){
    unique_gsl_matrix gsl_mat (gsl_matrix_alloc(m->rows(), m->cols()), gsl_matrix_free);
    auto expr = m->getMatrix().begin();
    for (size_t r = 0; r < m->rows(); ++r){
        for (size_t c = 0; c < m->cols(); ++c){
            gsl_matrix_set(gsl_mat.get(), r, c, (*(expr++))->value());
        }
    }
    return std::move(gsl_mat);
}
inline unique_gsl_matrix_complex make_complex_gsl_matrix(MatrixExpression* m){
    unique_gsl_matrix_complex gsl_mat (gsl_matrix_complex_alloc(m->rows(), m->cols()), gsl_matrix_complex_free);
    auto expr = m->getMatrix().begin();
    for (size_t r = 0; r < m->rows(); ++r){
        for (size_t c = 0; c < m->cols(); ++c){
            gsl_matrix_complex_set(gsl_mat.get(), r, c, (*(expr++))->complex());
        }
    }
    return std::move(gsl_mat);
}
inline unique_gsl_permutation make_gsl_permutation(MatrixExpression* m){
    unique_gsl_permutation gsl_perm (gsl_permutation_alloc(m->rows()), gsl_permutation_free);
    return std::move(gsl_perm);
}


expression fe_det(expression& arg, const Variables& vars){
    if (arg->matrix()){
        auto matrix = arg->evaluate(vars);
        if (matrix->isComplex()){
            auto gsl_mat = make_complex_gsl_matrix(matrix->matrix());
            auto gsl_perm = make_gsl_permutation(matrix->matrix());
            int signum;
            gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
            return make_unique<NumExpression>(
                gsl_linalg_complex_LU_det(gsl_mat.get(), signum)
            );
        }
        else{
            auto gsl_mat = make_gsl_matrix(matrix->matrix());
            auto gsl_perm = make_gsl_permutation(matrix->matrix());
            int signum;
            gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
            return make_unique<NumExpression>(
                gsl_linalg_LU_det(gsl_mat.get(), signum)
            );
        }
    }
    return make_unique<InvalidExpression>(Exception("Determinant expects a matrix expression"));
}