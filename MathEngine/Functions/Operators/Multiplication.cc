#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_blas.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    // @Operator mul: *
    struct mul: public OperatorFunctionExpression {
        mul(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = arg->at(1)->eval(vars);
            auto r = arg->at(2)->eval(vars);
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
        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            return l * r;
        }

        expression simplify() {
            auto l = arg->at(1);
            auto r = arg->at(2);
            return l * r;
        }
        expression derivative(const std::string& var) {
            auto l = arg->at(1);
            auto r = arg->at(2);
            return l->derivative(var) * r + l * r->derivative(var);
        }

        expression matrix_mul(expression lhs, expression rhs){
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
                );
            }
            if (lhs == MATRIX || rhs == MATRIX){
                auto scalar = lhs == MATRIX ? rhs : lhs;
                auto matrix = lhs == MATRIX ? lhs : rhs;
                if (scalar->isComplex() || matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    gsl_matrix_complex_scale(gsl_mat.get(), scalar->complex());
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    gsl_matrix_scale(gsl_mat.get(), scalar->value());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            throw Exception("Matrix multiplication requires at least one matrix operand.");
        }
    };
    MAKE_FUNCTION_EXPRESSION(mul)

}
