#pragma once

#include <memory>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

#include "../../InvalidExpression.h"
#include "../../MatrixExpression.h"
#include "../../NumericalExpression.h"
#include "../BinaryOperatorDirectory.h"
#include "../OperatorDirectory/BinaryOperators.h"

expression matrix_addition(MatrixExpression* lhs, MatrixExpression* rhs){
    if (lhs->rows() == rhs->rows() && lhs->cols() == rhs->cols()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            gsl_matrix_complex_add(lmat.get(), rmat.get());
            return std::make_unique<MatrixExpression>(lmat.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            gsl_matrix_add(lmat.get(), rmat.get());
            return std::make_unique<MatrixExpression>(lmat.get());
        }
    }
    return std::make_unique<InvalidExpression>(Exception(
        "Expected (m, n) + (m, n) matrix. Got: (",
        lhs->rows(), ", ", lhs->cols(), ") + (",
        rhs->rows(), ", ", rhs->cols(), ")"
    ));
}

expression matrix_scalar_addition(expression& scalar, MatrixExpression* mat, const Variables& vars){
    if (scalar->isComplex() || mat->isComplex()){
        auto gsl_mat = mat->to_gsl_matrix_complex();
        gsl_matrix_complex_add_constant(gsl_mat.get(), scalar->complex(vars));
        return std::make_unique<MatrixExpression>(gsl_mat.get());
    }
    else{
        auto gsl_mat = mat->to_gsl_matrix();
        gsl_matrix_add_constant(gsl_mat.get(), scalar->value(vars));
        return std::make_unique<MatrixExpression>(gsl_mat.get());
    }
}

expression fe_PLUS(expression& lhs, expression& rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->matrix() && rexpr->matrix()){
        return matrix_addition(lexpr->matrix(), rexpr->matrix());
    }
    if (lexpr->matrix()){
        return matrix_scalar_addition(rexpr, lexpr->matrix(), vars);
    }
    if (rexpr->matrix()){
        return matrix_scalar_addition(lexpr, rexpr->matrix(), vars);
    }
    if (lexpr->isComplex() || rexpr->isComplex()){
        return std::make_unique<NumExpression>(gsl_complex_add(lexpr->complex(), rexpr->complex()));
    }
    return std::make_unique<NumExpression>(f_PLUS(lexpr->value(vars), rexpr->value(vars)));
}
