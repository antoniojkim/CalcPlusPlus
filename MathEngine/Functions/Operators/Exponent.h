#pragma once

#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Scanner/scanner.h"
#include "../AbstractFunction.h"

namespace Function {

    // @Operator pow ^ **
    const struct __pow__: public OperatorFunction {
        __pow__(): OperatorFunction("^") {}
        expression evaluate(Function::Args& args) override {
            using Scanner::MATRIX;
            auto l = args["l"];
            auto r = args["r"];
            if (l == MATRIX){
                if (r == VAR && r->repr() == "T"){
                    return matrix_transpose(l);
                }
                else if (r->value() == -1){
                    return matrix_inverse(l);
                }
                throw Exception("Invalid Matrix Exponent: ", r);
            }
            if (l->isComplex() || r->isComplex()){
                return NumExpression::construct(gsl_complex_pow(l->complex(), r->complex()));
            }
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long) std::pow(l->value(), r->value()));
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long) std::pow(l->value(), r->value()));
            }
            return NumExpression::construct(std::pow(l->value(), r->value()));
        }
        expression derivative(Function::Args& args, const std::string& var) override {
            using ExpressionMath::ln;
            auto l = args["l"];
            auto r = args["r"];
            if (r->isEvaluable()){
                return (l ^ (r - 1)) * (l->derivative(var) * r);
            }
            else if (l->isEvaluable()){
                return (l ^ r) *  ln(l) * r->derivative(var);
            }
            else{
                return (l ^ (r - 1)) * (l->derivative(var) * r + l * ln(l) * r->derivative(var));
            }
        }


        expression matrix_inverse(expression matrix){
            if (matrix->shape(0) == matrix->shape(1)){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    gsl_linalg_complex_LU_invx(gsl_mat.get(), gsl_perm.get());
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    gsl_linalg_LU_invx(gsl_mat.get(), gsl_perm.get());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            throw Exception("Expected (m, m) matrix. Got: (", matrix->shape(0), ", ", matrix->shape(1), ")");
        }

        expression matrix_transpose(expression matrix){
            if (matrix->shape(0) == matrix->shape(1)){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    gsl_matrix_complex_transpose(gsl_mat.get());
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    gsl_matrix_transpose(gsl_mat.get());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            else {
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    auto transpose = make_gsl_matrix_complex(matrix->shape(1), matrix->shape(0));
                    gsl_matrix_complex_transpose_memcpy(transpose.get(), gsl_mat.get());
                    return MatrixExpression::construct(transpose);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    auto transpose = make_gsl_matrix(matrix->shape(1), matrix->shape(0));
                    gsl_matrix_transpose_memcpy(transpose.get(), gsl_mat.get());
                    return MatrixExpression::construct(transpose);
                }
            }
        }
    } pow;

}
