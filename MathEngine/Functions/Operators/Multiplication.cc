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
    namespace mul {
        expression matrix_mul(expression lhs, expression rhs);

        expression eval(Function::Args& args) {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = args.next();
            auto r = args.next();
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
        expression derivative(Function::Args& args, const std::string& var) {
            auto l = args.next();
            auto r = args.next();
            return l->derivative(var) * r + l * r->derivative(var);
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION('*')

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
    }

}
