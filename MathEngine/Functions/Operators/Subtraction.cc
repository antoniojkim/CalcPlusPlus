#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    // @Operator sub: -
    namespace sub {
        expression matrix_sub(expression lhs, expression rhs);

        expression eval(Function::Args& args) {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = args.next();
            auto r = args.next();
            if (l == MATRIX || r == MATRIX){
                return matrix_sub(l, r);
            }
            if (l->isComplex() || r->isComplex()){
                return NumExpression::construct(gsl_complex_sub(l->complex(), r->complex()));
            }
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long)(l->value() - r->value()));
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long)(l->value() - r->value()));
            }
            return NumExpression::construct(l->value() - r->value());
        }
        expression simplify(Function::Args& args) {
            auto l = args.next();
            auto r = args.next();
            return l - r;
        }
        expression derivative(Function::Args& args, const std::string& var) {
            auto l = args.next();
            auto r = args.next();
            return l->derivative(var) - r->derivative(var);
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION('-')

        expression matrix_sub(expression lhs, expression rhs){
            using Scanner::MATRIX;
            if (lhs == MATRIX && rhs == MATRIX){
                if (lhs->shape(0) == rhs->shape(0) && lhs->shape(1) == rhs->shape(1)){
                    if (lhs->isComplex() || rhs->isComplex()){
                        auto lmat = to_gsl_matrix_complex(lhs);
                        auto rmat = to_gsl_matrix_complex(rhs);
                        gsl_matrix_complex_sub(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                    else{
                        auto lmat = to_gsl_matrix(lhs);
                        auto rmat = to_gsl_matrix(rhs);
                        gsl_matrix_sub(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                }
                throw Exception("operands could not be broadcast together with shapes (",
                    lhs->shape(0), ",", lhs->shape(1), ") and (", rhs->shape(0), ",", rhs->shape(1), ")");
            }
            if (lhs == MATRIX){
                if (lhs->isComplex() || rhs->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(lhs);
                    gsl_matrix_complex_add_constant(gsl_mat.get(), gsl_complex_negative(rhs->complex()));
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(lhs);
                    gsl_matrix_add_constant(gsl_mat.get(), -rhs->value());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            if (rhs == MATRIX){
                if (lhs->isComplex() || rhs->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(rhs);
                    gsl_matrix_complex_scale(gsl_mat.get(), gsl_complex{-1, 0});
                    gsl_matrix_complex_add_constant(gsl_mat.get(), lhs->complex());
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(rhs);
                    gsl_matrix_scale(gsl_mat.get(), -1);
                    gsl_matrix_add_constant(gsl_mat.get(), lhs->value());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            throw Exception("Matrix subtraction requires at least one matrix operand.");
        }
    }

}
