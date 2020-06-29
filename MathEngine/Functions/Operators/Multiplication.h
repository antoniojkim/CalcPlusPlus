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

    // @Operator mul *
    const struct __mul__: public OperatorFunction {
        __mul__(): OperatorFunction("*") {}
        expression evaluate(Function::Args& args) override {
            using Scanner::MATRIX;
            auto l = args["l"];
            auto r = args["r"];
            if (l == MATRIX || r == MATRIX){
                return matrix_mul(l, r);
            }
            if (l->isComplex() || r->isComplex()){
                return NumExpression::construct(gsl_complex_mul(l->complex(), r->complex()));
            }
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long)(l->value() * r->value()));
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long)(l->value() * r->value()));
            }
            return NumExpression::construct(l->value() * r->value());
        }
        expression derivative(Function::Args& args, const std::string& var) override {
            auto l = args["l"];
            auto r = args["r"];
            return l->derivative(var) * r + l * r->derivative(var);
        }

        static expression matrix_mul(expression lhs, expression rhs){
            using Scanner::MATRIX;
            if (lhs == MATRIX && rhs == MATRIX){
                if (lhs->shape(1) == rhs->shape(0)){
                    if (lhs->isComplex() || rhs->isComplex()){
                        auto lmat = to_gsl_matrix_complex(lhs);
                        auto rmat = to_gsl_matrix_complex(rhs);
                        auto result = make_gsl_matrix_complex(lhs->shape(0), rhs->shape(1));
                        gsl_blas_zgemm(CblasNoTrans, CblasNoTrans,
                                        gsl_complex{1.0}, lmat.get(), rmat.get(),
                                        gsl_complex{0.0}, result.get());
                        return MatrixExpression::construct(result);
                    }
                    else{
                        auto lmat = to_gsl_matrix(lhs);
                        auto rmat = to_gsl_matrix(rhs);
                        auto result = make_gsl_matrix(lhs->shape(0), rhs->shape(1));
                        gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                                        1.0, lmat.get(), rmat.get(),
                                        0.0, result.get());
                        return MatrixExpression::construct(result);
                    }
                }
                if (lhs->shape(0) == rhs->shape(0) && lhs->shape(1) == rhs->shape(1)){
                    if (lhs->isComplex() || rhs->isComplex()){
                        auto lmat = to_gsl_matrix_complex(lhs);
                        auto rmat = to_gsl_matrix_complex(rhs);
                        gsl_matrix_complex_mul_elements(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                    else{
                        auto lmat = to_gsl_matrix(lhs);
                        auto rmat = to_gsl_matrix(rhs);
                        gsl_matrix_mul_elements(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                }
                throw Exception(
                    "Matrix multiplication expected (m, n)*(n, p) matrix or (m, n)*(m, n) matrix. Got: (",
                    lhs->shape(0), ", ", lhs->shape(1), ")*(",
                    rhs->shape(0), ", ", rhs->shape(1), ")"
                ));
            }
            if (lhs == MATRIX || rhs == MATRIX){
                auto scalar = lhs == MATRIX ? rhs : lhs;
                auto matrix = lhs == MATRIX ? lhs : rhs;
                if (scalar->isComplex() || mat->isComplex()){
                    auto gsl_mat = mat->to_gsl_matrix_complex();
                    gsl_matrix_complex_scale(gsl_mat.get(), scalar->complex());
                    return MatrixExpression::construct(gsl_mat.get());
                }
                else{
                    auto gsl_mat = mat->to_gsl_matrix();
                    gsl_matrix_scale(gsl_mat.get(), scalar->value());
                    return MatrixExpression::construct(gsl_mat.get());
                }
            }
            throw Exception("Matrix multiplication requires at least one matrix operand.");
        }
    } mul;

}