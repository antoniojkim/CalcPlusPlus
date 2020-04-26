#pragma once

#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

#include "../../InvalidExpression.h"
#include "../../MatrixExpression.h"
#include "../../NumericalExpression.h"
#include "../../UnitExpression.h"
#include "../BinaryOperatorDirectory.h"
#include "../OperatorDirectory/BinaryOperators.h"

expression matrix_division(MatrixExpression* lhs, MatrixExpression* rhs){
    if (lhs->rows() == rhs->rows() && lhs->cols() == rhs->cols()){
        if (lhs->isComplex() || rhs->isComplex()){
            auto lmat = lhs->to_gsl_matrix_complex();
            auto rmat = rhs->to_gsl_matrix_complex();
            gsl_matrix_complex_div_elements(lmat.get(), rmat.get());
            return MatrixExpression::construct(lmat.get());
        }
        else{
            auto lmat = lhs->to_gsl_matrix();
            auto rmat = rhs->to_gsl_matrix();
            gsl_matrix_div_elements(lmat.get(), rmat.get());
            return MatrixExpression::construct(lmat.get());
        }
    }
    return InvalidExpression::construct(Exception(
        "Expected (m, n) + (m, n) matrix. Got: (",
        lhs->rows(), ", ", lhs->cols(), ") + (",
        rhs->rows(), ", ", rhs->cols(), ")"
    ));
}

expression matrix_scalar_division(expression& scalar, MatrixExpression* mat, const Variables& vars){
    if (scalar->isComplex() || mat->isComplex()){
        auto gsl_mat = mat->to_gsl_matrix_complex();
        auto scalar_mat = make_gsl_matrix_complex(mat->rows(), mat->cols());
        gsl_matrix_complex_set_all(scalar_mat.get(), scalar->complex(vars));
        gsl_matrix_complex_div_elements(scalar_mat.get(), gsl_mat.get());
        return MatrixExpression::construct(scalar_mat.get());
    }
    else{
        auto gsl_mat = mat->to_gsl_matrix();
        auto scalar_mat = make_gsl_matrix(mat->rows(), mat->cols());
        gsl_matrix_set_all(scalar_mat.get(), scalar->value(vars));
        gsl_matrix_div_elements(scalar_mat.get(), gsl_mat.get());
        return MatrixExpression::construct(scalar_mat.get());
    }
}

expression matrix_scalar_division(MatrixExpression* mat, expression& scalar, const Variables& vars){
    if (scalar->isComplex() || mat->isComplex()){
        auto gsl_mat = mat->to_gsl_matrix_complex();
        gsl_matrix_complex_scale(gsl_mat.get(), gsl_complex_inverse(scalar->complex(vars)));
        return MatrixExpression::construct(gsl_mat.get());
    }
    else{
        auto gsl_mat = mat->to_gsl_matrix();
        gsl_matrix_scale(gsl_mat.get(), 1.0 / scalar->value(vars));
        return MatrixExpression::construct(gsl_mat.get());
    }
}

inline expression unit_conversion_division(UnitExpression* unit1, UnitExpression* unit2){
    return (*unit1) / (*unit2);
}
inline expression unit_conversion_division(UnitExpression* unit1, expression& expr){
    return (*unit1) / expr;
}

expression fe_SLASH(expression& lhs, expression& rhs, const Variables& vars){
    auto lexpr = lhs->evaluate(vars);
    auto rexpr = rhs->evaluate(vars);
    if (lexpr->matrix() && rexpr->matrix()){
        return matrix_division(lexpr->matrix(), rexpr->matrix());
    }
    if (lexpr->matrix()){
        return matrix_scalar_division(lexpr->matrix(), rexpr, vars);
    }
    if (rexpr->matrix()){
        return matrix_scalar_division(lexpr, rexpr->matrix(), vars);
    }
    if (lexpr->unit()){
        if (rexpr->unit()){
            return unit_conversion_division(lexpr->unit(), rexpr->unit());
        }
        return unit_conversion_division(lexpr->unit(), rexpr);
    }
    if (lexpr->isComplex() || rexpr->isComplex()){
        return NumExpression::construct(gsl_complex_div(lexpr->complex(vars), rexpr->complex(vars)));
    }
    return NumExpression::construct(f_SLASH(lexpr->value(vars), rexpr->value(vars)));

}
