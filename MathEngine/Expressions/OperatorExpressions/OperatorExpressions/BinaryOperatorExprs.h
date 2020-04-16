#pragma once

#include <memory>
#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>

#include "../../InvalidExpression.h"
#include "../../NumericalExpression.h"
#include "../../MatrixExpression.h"
#include "../BinaryOperatorDirectory.h"
#include "../OperatorDirectory/BinaryOperators.h"

expression matrix_multiplication(MatrixExpression* lhs, MatrixExpression* rhs){
    if (lhs->cols() == rhs->rows()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            auto result = make_gsl_matrix_complex(lhs->rows(), rhs->cols());
            gsl_blas_zgemm(CblasNoTrans, CblasNoTrans,
                           gsl_complex{1.0}, lmat.get(), rmat.get(),
                           gsl_complex{0.0}, result.get());
            return std::make_unique<MatrixExpression>(result.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            auto result = make_gsl_matrix(lhs->rows(), rhs->cols());
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                           1.0, lmat.get(), rmat.get(),
                           0.0, result.get());
            return std::make_unique<MatrixExpression>(result.get());
        }
    }
    else if (lhs->rows() == rhs->rows() && lhs->cols() == rhs->cols()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            gsl_matrix_complex_mul_elements(lmat.get(), rmat.get());
            return std::make_unique<MatrixExpression>(lmat.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            gsl_matrix_mul_elements(lmat.get(), rmat.get());
            return std::make_unique<MatrixExpression>(lmat.get());
        }
    }
    return std::make_unique<InvalidExpression>(Exception(
        "Expected (m, n)*(n, p) matrix or (m, n)*(m, n) matrix. Got: (",
        lhs->rows(), ", ", lhs->cols(), ")*(",
        rhs->rows(), ", ", rhs->cols(), ")"
    ));
}

expression fe_STAR(expression& lhs, expression& rhs, const Variables& vars){
    if (lhs->matrix() && rhs->matrix()){
        return matrix_multiplication(lhs->matrix(), rhs->matrix());
    }
    return std::make_unique<NumExpression>(f_STAR(lhs->value(vars), rhs->value(vars)));
}
