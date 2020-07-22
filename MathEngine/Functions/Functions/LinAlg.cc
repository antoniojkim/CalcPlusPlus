#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/FunctionExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {
    // @Function det
    struct det: public FunctionExpression {
        det(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"m", Empty}}) {}  // Signature: (m)
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto matrix = arg->at(0)->eval(vars);
            if (matrix == MATRIX && matrix->size() > 0){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return NumExpression::construct(gsl_linalg_complex_LU_det(gsl_mat.get(), signum));
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return NumExpression::construct(gsl_linalg_LU_det(gsl_mat.get(), signum));
                }
            }
            throw Exception("det expected a non-empty matrix. Got: ", matrix);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(det)

    // @Function lndet
    struct lndet: public FunctionExpression {
        lndet(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"m", Empty}}) {}  // Signature: (m)
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto matrix = arg->at(0)->eval(vars);
            if (matrix == MATRIX && matrix->size() > 0){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return NumExpression::construct(gsl_linalg_complex_LU_lndet(gsl_mat.get()));
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return NumExpression::construct(gsl_linalg_LU_lndet(gsl_mat.get()));
                }
            }
            throw Exception("lndet expected non-empty matrix. Got: ", matrix);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(lndet)

    // @Function LU
    struct LU: public FunctionExpression {
        LU(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"m", Empty}}) {}  // Signature: (m)
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto matrix = arg->at(0)->eval(vars);
            if (matrix == MATRIX && matrix->size() > 0){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return TupleExpression::construct({
                        VariableExpression::construct("LU", MatrixExpression::construct(gsl_mat)),
                        VariableExpression::construct("P", MatrixExpression::construct(gsl_perm)),
                        VariableExpression::construct("sign", NumExpression::construct(signum))
                    });
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return TupleExpression::construct({
                        VariableExpression::construct("LU", MatrixExpression::construct(gsl_mat)),
                        VariableExpression::construct("P", MatrixExpression::construct(gsl_perm)),
                        VariableExpression::construct("sign", NumExpression::construct(signum))
                    });
                }
            }
            throw Exception("LU Factorization expects a non-empty matrix. Got: ", matrix);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(LU)

    // @Function LUsolve: solve
    struct LUsolve: public FunctionExpression {
        LUsolve(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (A, b)
                {"A", Empty}, {"b", Empty}
            }) {}
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto A = arg->at(0)->eval(vars);
            auto b = arg->at(1)->eval(vars);
            if (A == MATRIX && b == MATRIX && (A->shape(0) == b->size())){
                if (A->isComplex() || b->isComplex()){
                    auto LU = to_gsl_matrix_complex(A);
                    auto perm = to_gsl_permutation(A);
                    auto x = to_gsl_vector_complex(b);
                    int signum;
                    gsl_linalg_complex_LU_decomp(LU.get(), perm.get(), &signum);
                    gsl_linalg_complex_LU_svx(LU.get(), perm.get(), x.get());
                    return MatrixExpression::construct(x);
                }
                else{
                    auto LU = to_gsl_matrix(A);
                    auto perm = to_gsl_permutation(A);
                    auto x = to_gsl_vector(b);
                    int signum;
                    gsl_linalg_LU_decomp(LU.get(), perm.get(), &signum);
                    gsl_linalg_LU_svx(LU.get(), perm.get(), x.get());
                    return MatrixExpression::construct(x);
                }
            }
            throw Exception("LU Solve expects a (m, n) matrix and a (n) vector. Got: ", arg);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(LUsolve)

    // @Function Cholesky: Chol
    struct Cholesky: public FunctionExpression {
        Cholesky(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"m", Empty}}) {}  // Signature: (m)
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto matrix = arg->at(0)->eval(vars);
            if (matrix == MATRIX && matrix->size() > 0){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    int code = gsl_linalg_complex_cholesky_decomp(gsl_mat.get());
                    if (code != 0){
                        throw Exception("Cholesky decomposition expects a positive definite matrix");
                    }
                    return MatrixExpression::construct(gsl_mat);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    int code = gsl_linalg_cholesky_decomp1(gsl_mat.get());
                    if (code != 0){
                        throw Exception("Cholesky decomposition expects a positive definite matrix");
                    }
                    return MatrixExpression::construct(gsl_mat);
                }
            }
            throw Exception("Cholesky decomposition expects a non-empty matrix. Got: ", matrix);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(Cholesky)

    // @Function SVD
    struct SVD: public FunctionExpression {
        SVD(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"m", Empty}}) {}  // Signature: (m)
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto matrix = arg->at(0)->eval(vars);
            if (matrix == MATRIX && matrix->size() > 0){
                if (matrix->isComplex()){
                    throw Exception("Cannot compute SVD of complex matrix");
                }
                else{
                    size_t n = matrix->shape(1);
                    auto A = to_gsl_matrix(matrix);
                    auto V = make_gsl_matrix(n, n);
                    auto S = make_gsl_vector(n);
                    auto work = make_gsl_vector(n);
                    int code = gsl_linalg_SV_decomp(A.get(), V.get(), S.get(), work.get());
                    if (code != 0){
                        throw Exception("SVD failed on matrix: ", matrix);
                    }
                    return TupleExpression::construct({
                        VariableExpression::construct("U", MatrixExpression::construct(A)),
                        VariableExpression::construct("S", MatrixExpression::construct(S)),
                        VariableExpression::construct("V", MatrixExpression::construct(V))
                    });
                }
            }
            throw Exception("SVD expects a non-empty matrix. Got: ", matrix);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(SVD)
}
