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
    struct div: public OperatorFunctionExpression {
        div(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = arg->at(1)->eval(vars);
            auto r = arg->at(2)->eval(vars);
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
        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            return l / r;
        }

        expression simplify() {
            auto l = arg->at(1);
            auto r = arg->at(2);
            return l / r;
        }
        expression derivative(const std::string& var) {
            auto l = arg->at(1);
            auto r = arg->at(2);
            return (l->derivative(var) * r - l * r->derivative(var)) / (r ^ 2);
        }

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
    };
    MAKE_FUNCTION_EXPRESSION(div)


    // @Operator mod: %
    struct mod: public OperatorFunctionExpression {
        mod(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = arg->at(1)->eval(vars);
            auto r = arg->at(2)->eval(vars);
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
        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            return std::fmod(l, r);
        }
    };
    MAKE_FUNCTION_EXPRESSION(mod)


    // @Operator floordiv: //
    struct floordiv: public OperatorFunctionExpression {
        floordiv(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN;
            auto l = arg->at(1)->eval(vars);
            auto r = arg->at(2)->eval(vars);
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
        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(1)->value(vars);
            double r = arg->at(2)->value(vars);
            double intpart;
            std::modf(l / r, &intpart);
            return intpart;
        }
    };
    MAKE_FUNCTION_EXPRESSION(floordiv)

}
