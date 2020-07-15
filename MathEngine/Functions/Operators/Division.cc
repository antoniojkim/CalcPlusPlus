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

    // @Operator div: /
    namespace div {
        expression matrix_div(expression lhs, expression rhs);

        expression eval(Function::Args& args) {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = args.next();
            auto r = args.next();
            if (l == MATRIX || r == MATRIX){
                return matrix_div(l, r);
            }
            if (l->isComplex() || r->isComplex()){
                return NumExpression::construct(gsl_complex_div(l->complex(), r->complex()));
            }
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long)(l->value() / r->value()));
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long)(l->value() / r->value()));
            }
            return NumExpression::construct(l->value() / r->value());
        }
        expression derivative(Function::Args& args, const std::string& var) {
            auto l = args.next();
            auto r = args.next();
            return (l->derivative(var) * r - l * r->derivative(var)) / (r ^ 2);
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION('/')

        expression matrix_div(expression lhs, expression rhs){
            using Scanner::MATRIX;
            if (lhs == MATRIX && rhs == MATRIX){
                if (lhs->shape(0) == rhs->shape(0) && lhs->shape(1) == rhs->shape(1)){
                    if (lhs->isComplex() || rhs->isComplex()){
                        auto lmat = to_gsl_matrix_complex(lhs);
                        auto rmat = to_gsl_matrix_complex(rhs);
                        gsl_matrix_complex_div_elements(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                    else{
                        auto lmat = to_gsl_matrix(lhs);
                        auto rmat = to_gsl_matrix(rhs);
                        gsl_matrix_div_elements(lmat.get(), rmat.get());
                        return MatrixExpression::construct(lmat);
                    }
                }
                throw Exception("operands could not be broadcast together with shapes (",
                    lhs->shape(0), ",", lhs->shape(1), ") and (", rhs->shape(0), ",", rhs->shape(1), ")");
            }
            if (lhs == MATRIX){
                if (lhs->isComplex() || rhs->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(lhs);
                    auto scalar_mat = make_gsl_matrix_complex(lhs->shape(0), lhs->shape(1));
                    gsl_matrix_complex_set_all(scalar_mat.get(), rhs->complex());
                    gsl_matrix_complex_div_elements(gsl_mat.get(), scalar_mat.get());
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(lhs);
                    auto scalar_mat = make_gsl_matrix(lhs->shape(0), lhs->shape(1));
                    gsl_matrix_set_all(scalar_mat.get(), rhs->value());
                    gsl_matrix_div_elements(gsl_mat.get(), scalar_mat.get());
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            if (rhs == MATRIX){
                if (lhs->isComplex() || rhs->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(rhs);
                    auto scalar_mat = make_gsl_matrix_complex(rhs->shape(0), rhs->shape(1));
                    gsl_matrix_complex_set_all(scalar_mat.get(), lhs->complex());
                    gsl_matrix_complex_div_elements(scalar_mat.get(), gsl_mat.get());
                    return MatrixExpression::construct(scalar_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(rhs);
                    auto scalar_mat = make_gsl_matrix(rhs->shape(0), rhs->shape(1));
                    gsl_matrix_set_all(scalar_mat.get(), lhs->value());
                    gsl_matrix_div_elements(scalar_mat.get(), gsl_mat.get());
                    return MatrixExpression::construct(scalar_mat);
                }
            }
            throw Exception("Matrix division requires at least one matrix operand.");
        }
    }


    // @Operator mod: %
    namespace mod {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = args.next();
            auto r = args.next();
            if (l->isComplex() || r->isComplex()){
                throw Exception("Arithmetic Error: cannot modulo divide complex numbers.");
            }
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long) std::fmod(l->value(), r->value()));
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long) std::fmod(l->value(), r->value()));
            }
            return NumExpression::construct(std::fmod(l->value(), r->value()));
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION('%')
    }


    // @Operator floordiv: //
    namespace floordiv {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = args.next();
            auto r = args.next();
            if (l->isComplex() || r->isComplex()){
                throw Exception("Arithmetic Error: cannot floor divide complex numbers.");
            }
            double intpart;
            std::modf(l->value() / r->value(), &intpart);
            if (l == HEX || r == HEX){
                return HexExpression::construct((unsigned long long) intpart);
            }
            if (l == BIN || r == BIN){
                return BinExpression::construct((unsigned long long) intpart);
            }
            return NumExpression::construct(intpart);
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION("//")
    }

}
