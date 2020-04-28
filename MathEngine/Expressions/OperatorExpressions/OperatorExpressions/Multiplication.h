#pragma once

#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>

#include "../../InvalidExpression.h"
#include "../../NumericalExpression.h"
#include "../../MatrixExpression.h"
#include "../../UnitExpression.h"
#include "../BinaryOperatorDirectory.h"
#include "../OperatorDirectory/BinaryOperators.h"

expression matrix_multiplication(const MatrixExpression* lhs, const MatrixExpression* rhs){
    if (lhs->cols() == rhs->rows()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            auto result = make_gsl_matrix_complex(lhs->rows(), rhs->cols());
            gsl_blas_zgemm(CblasNoTrans, CblasNoTrans,
                           gsl_complex{1.0}, lmat.get(), rmat.get(),
                           gsl_complex{0.0}, result.get());
            return MatrixExpression::construct(result.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            auto result = make_gsl_matrix(lhs->rows(), rhs->cols());
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                           1.0, lmat.get(), rmat.get(),
                           0.0, result.get());
            return MatrixExpression::construct(result.get());
        }
    }
    else if (lhs->rows() == rhs->rows() && lhs->cols() == rhs->cols()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            gsl_matrix_complex_mul_elements(lmat.get(), rmat.get());
            return MatrixExpression::construct(lmat.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            gsl_matrix_mul_elements(lmat.get(), rmat.get());
            return MatrixExpression::construct(lmat.get());
        }
    }
    return InvalidExpression::construct(Exception(
        "Expected (m, n)*(n, p) matrix or (m, n)*(m, n) matrix. Got: (",
        lhs->rows(), ", ", lhs->cols(), ")*(",
        rhs->rows(), ", ", rhs->cols(), ")"
    ));
}

expression matrix_scalar_multiply(const expression scalar, const MatrixExpression* mat, const Variables& vars){
    if (scalar->isComplex() || mat->isComplex()){
        auto gsl_mat = mat->to_gsl_matrix_complex();
        gsl_matrix_complex_scale(gsl_mat.get(), scalar->complex(vars));
        return MatrixExpression::construct(gsl_mat.get());
    }
    else{
        auto gsl_mat = mat->to_gsl_matrix();
        gsl_matrix_scale(gsl_mat.get(), scalar->value(vars));
        return MatrixExpression::construct(gsl_mat.get());
    }
}

inline expression unit_conversion_multiply(const BaseUnitExpression* unit1, const BaseUnitExpression* unit2){
    return (*unit1) * (*unit2);
}
inline expression unit_conversion_multiply(const BaseUnitExpression* unit1, const expression expr){
    return (*unit1) * expr;
}

expression fe_STAR(const expression lhs, const expression rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->matrix() && rexpr->matrix()){
        return matrix_multiplication(lexpr->matrix(), rexpr->matrix());
    }
    if (lexpr->matrix()){
        return matrix_scalar_multiply(rexpr, lexpr->matrix(), vars);
    }
    if (rexpr->matrix()){
        return matrix_scalar_multiply(lexpr, rexpr->matrix(), vars);
    }
    if (lexpr->unit() && rexpr->unit()){
        return unit_conversion_multiply(lexpr->unit(), rexpr->unit());
    }
    if (lexpr->unit()){
        return unit_conversion_multiply(lexpr->unit(), rexpr);
    }
    if (rexpr->unit()){
        return unit_conversion_multiply(rexpr->unit(), lexpr);
    }
    if (lexpr->hex() || rexpr->hex()){
        return HexExpression::construct((unsigned long long) (lexpr->value() * rexpr->value()));
    }
    if (lexpr->bin() || rexpr->bin()){
        return BinExpression::construct((unsigned long long) (lexpr->value() * rexpr->value()));
    }
    if (lexpr->isComplex() || rexpr->isComplex()){
        return NumExpression::construct(gsl_complex_mul(lexpr->complex(vars), rexpr->complex(vars)));
    }
    return NumExpression::construct(f_STAR(lexpr->value(vars), rexpr->value(vars)));
}
