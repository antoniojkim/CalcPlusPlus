#pragma once

#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

#include "../../InvalidExpression.h"
#include "../../MatrixExpression.h"
#include "../../NumericalExpression.h"
#include "../OperatorDirectory.h"
#include "../Operators/BinaryOperators.h"

expression matrix_subtraction(const MatrixExpression* lhs, const MatrixExpression* rhs){
    if (lhs->rows() == rhs->rows() && lhs->cols() == rhs->cols()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            gsl_matrix_complex_sub(lmat.get(), rmat.get());
            return MatrixExpression::construct(lmat.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            gsl_matrix_sub(lmat.get(), rmat.get());
            return MatrixExpression::construct(lmat.get());
        }
    }
    return InvalidExpression::construct(Exception(
        "Expected (m, n) + (m, n) matrix. Got: (",
        lhs->rows(), ", ", lhs->cols(), ") + (",
        rhs->rows(), ", ", rhs->cols(), ")"
    ));
}

expression matrix_scalar_subtraction(const expression scalar, const MatrixExpression* mat, const Variables& vars){
    if (scalar->isComplex() || mat->isComplex()){
        auto gsl_mat = mat->to_gsl_matrix_complex();
        gsl_matrix_complex_scale(gsl_mat.get(), gsl_complex{-1, 0});
        gsl_matrix_complex_add_constant(gsl_mat.get(), scalar->complex(vars));
        return MatrixExpression::construct(gsl_mat.get());
    }
    else{
        auto gsl_mat = mat->to_gsl_matrix();
        gsl_matrix_scale(gsl_mat.get(), -1);
        gsl_matrix_add_constant(gsl_mat.get(), scalar->value(vars));
        return MatrixExpression::construct(gsl_mat.get());
    }
}

expression matrix_scalar_subtraction(const MatrixExpression* mat, const expression scalar, const Variables& vars){
    if (scalar->isComplex() || mat->isComplex()){
        auto gsl_mat = mat->to_gsl_matrix_complex();
        gsl_matrix_complex_add_constant(gsl_mat.get(), gsl_complex_negative(scalar->complex(vars)));
        return MatrixExpression::construct(gsl_mat.get());
    }
    else{
        auto gsl_mat = mat->to_gsl_matrix();
        gsl_matrix_add_constant(gsl_mat.get(), -scalar->value(vars));
        return MatrixExpression::construct(gsl_mat.get());
    }
}

expression fe_MINUS(const expression lhs, const expression rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->matrix() && rexpr->matrix()){
        return matrix_subtraction(lexpr->matrix(), rexpr->matrix());
    }
    if (lexpr->matrix()){
        return matrix_scalar_subtraction(lexpr->matrix(), rexpr, vars);
    }
    if (rexpr->matrix()){
        return matrix_scalar_subtraction(lexpr, rexpr->matrix(), vars);
    }
    if (lexpr->hex() || rexpr->hex()){
        return HexExpression::construct((unsigned long long) (lexpr->value() - rexpr->value()));
    }
    if (lexpr->bin() || rexpr->bin()){
        return BinExpression::construct((unsigned long long) (lexpr->value() - rexpr->value()));
    }
    if (lexpr->isComplex() || rexpr->isComplex()){
        return NumExpression::construct(gsl_complex_sub(lexpr->complex(), rexpr->complex()));
    }
    return NumExpression::construct(f_MINUS(lexpr->value(vars), rexpr->value(vars)));
}
