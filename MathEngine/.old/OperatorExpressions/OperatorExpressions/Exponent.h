#pragma once

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

#include "../../InvalidExpression.h"
#include "../../NumericalExpression.h"
#include "../../MatrixExpression.h"
#include "../../UnitExpression.h"
#include "../../VariableExpression.h"
#include "../OperatorDirectory.h"
#include "../Operators/BinaryOperators.h"

expression matrix_inverse(const MatrixExpression* matrix){
    if (matrix->rows() == matrix->cols()){
        if (matrix->isComplex()){
            auto gsl_mat = matrix->to_gsl_matrix_complex();
            auto gsl_perm = matrix->to_gsl_permutation();
            int signum;
            gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
            gsl_linalg_complex_LU_invx(gsl_mat.get(), gsl_perm.get());
            return MatrixExpression::construct(gsl_mat.get());
        }
        else{
            auto gsl_mat = matrix->to_gsl_matrix();
            auto gsl_perm = matrix->to_gsl_permutation();
            int signum;
            gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
            gsl_linalg_LU_invx(gsl_mat.get(), gsl_perm.get());
            return MatrixExpression::construct(gsl_mat.get());
        }
    }
    return InvalidExpression::construct(Exception(
        "Expected (m, m) matrix. Got: (",
        matrix->rows(), ", ", matrix->cols(), ")"
    ));
}

expression matrix_transpose(const MatrixExpression* matrix){
    if (matrix->rows() == matrix->cols()){
        if (matrix->isComplex()){
            auto gsl_mat = matrix->to_gsl_matrix_complex();
            gsl_matrix_complex_transpose(gsl_mat.get());
            return MatrixExpression::construct(gsl_mat.get());
        }
        else{
            auto gsl_mat = matrix->to_gsl_matrix();
            gsl_matrix_transpose(gsl_mat.get());
            return MatrixExpression::construct(gsl_mat.get());
        }
    }
    else {
        if (matrix->isComplex()){
            auto gsl_mat = matrix->to_gsl_matrix_complex();
            auto transpose = make_gsl_matrix_complex(matrix->cols(), matrix->rows());
            gsl_matrix_complex_transpose_memcpy(transpose.get(), gsl_mat.get());
            return MatrixExpression::construct(transpose.get());
        }
        else{
            auto gsl_mat = matrix->to_gsl_matrix();
            auto transpose = make_gsl_matrix(matrix->cols(), matrix->rows());
            gsl_matrix_transpose_memcpy(transpose.get(), gsl_mat.get());
            return MatrixExpression::construct(transpose.get());
        }
    }
    return InvalidExpression::construct(Exception(
        "Expected (m, m) matrix. Got: (",
        matrix->rows(), ", ", matrix->cols(), ")"
    ));
}

inline expression unit_conversion_pow(const BaseUnitExpression* unit1, const expression expr){
    return (*unit1) ^ expr;
}

expression fe_CARET(const expression lhs, const expression rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->matrix()){
        if (rexpr->variable() && rexpr->variable()->getName() == "T"){
            return matrix_transpose(lexpr->matrix());
        }
        else if (rexpr->value() == -1){
            return matrix_inverse(lexpr->matrix());
        }
        return InvalidExpression::construct(Exception("Invalid Matrix Exponent."));
    }
    if (lexpr->unit()){
        return unit_conversion_pow(lexpr->unit(), rexpr);
    }
    if (lexpr->hex() || rexpr->hex()){
        return HexExpression::construct((unsigned long long) pow(lexpr->value(), rexpr->value()));
    }
    if (lexpr->bin() || rexpr->bin()){
        return BinExpression::construct((unsigned long long) pow(lexpr->value(), rexpr->value()));
    }
    if (lexpr->isComplex() || rexpr->isComplex()){
        return NumExpression::construct(gsl_complex_pow(lexpr->complex(vars), rexpr->complex(vars)));
    }
    return NumExpression::construct(f_CARET(lexpr->value(vars), rexpr->value(vars)));
}

OperatorExpr fe_STAR_STAR = fe_CARET;
