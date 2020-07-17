#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    // @Operator add: +
    namespace add {
        expression matrix_add(expression lhs, expression rhs);

        expression eval(Function::Args& args) {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = args.next();
            auto r = args.next();
            if (l == MATRIX || r == MATRIX){
                return matrix_add(l, r);
            }
            if (l->isComplex() || r->isComplex()){
                return NumExpression::construct(gsl_complex_add(l->complex(), r->complex()));
            }
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long)(l->value() + r->value()));
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long)(l->value() + r->value()));
            }
            return NumExpression::construct(l->value() + r->value());
        }
        expression simplify(Function::Args& args) {
            auto l = args.next();
            auto r = args.next();
            return l + r;
        }
        expression derivative(Function::Args& args, const std::string& var) {
            auto l = args.next();
            auto r = args.next();
            return l->derivative(var) + r->derivative(var);
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION('+')

        expression matrix_add(expression lhs, expression rhs){
            using Scanner::MATRIX;
            if (lhs == MATRIX && rhs == MATRIX){
                if (lhs->shape(0) == rhs->shape(0) && lhs->shape(1) == rhs->shape(1)){
                    if (lhs->isComplex() || rhs->isComplex()){
                        auto lmat = to_gsl_matrix_complex(lhs);
                        auto rmat = to_gsl_matrix_complex(rhs);
                        gsl_matrix_complex_add(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                    else{
                        auto lmat = to_gsl_matrix(lhs);
                        auto rmat = to_gsl_matrix(rhs);
                        gsl_matrix_add(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                }
                throw Exception("operands could not be broadcast together with shapes (",
                    lhs->shape(0), ",", lhs->shape(1), ") and (", rhs->shape(0), ",", rhs->shape(1), ")");
            }
            if (lhs == MATRIX || rhs == MATRIX){
                auto scalar = lhs == MATRIX ? rhs : lhs;
                auto matrix = lhs == MATRIX ? lhs : rhs;
                if (scalar->isComplex() || matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    gsl_matrix_complex_add_constant(gsl_mat.get(), scalar->complex());
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    gsl_matrix_add_constant(gsl_mat.get(), scalar->value());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            throw Exception("Matrix addition requires at least one matrix operand.");
        }
    }

}
