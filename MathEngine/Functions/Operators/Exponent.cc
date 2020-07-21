#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_linalg.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {

    // @Operator pow: ^ **
    struct pow: public OperatorFunctionExpression {
        pow(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX, Scanner::HEX, Scanner::BIN, Scanner::VAR;
            auto l = arg->at(0)->eval(vars);
            auto r = arg->at(1)->eval(vars);
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
            if (!l->isEvaluable() || !r->isEvaluable()){
                return l ^ r;
            }
            return NumExpression::construct(std::pow(l->value(), r->value()));
        }
        double value(const Variables& vars = emptyVars) const override {
            double l = arg->at(0)->value(vars);
            double r = arg->at(1)->value(vars);
            return std::pow(l, r);
        }

        expression derivative(const std::string& var) {
            using ExpressionMath::ln;
            auto l = arg->at(0);
            auto r = arg->at(1);
            if (r->isNumber()){
                return (l ^ (r - 1)) * (l->derivative(var) * r);
            }
            else if (l->isNumber()){
                return (l ^ r) *  ln(l) * r->derivative(var);
            }
            else{
                return (l ^ (r - 1)) * (l->derivative(var) * r + l * ln(l) * r->derivative(var));
            }
        }


        expression matrix_inverse(expression matrix) {
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

        expression matrix_transpose(expression matrix) {
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
    };
    MAKE_FUNCTION_EXPRESSION(pow)

}
