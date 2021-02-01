#include <algorithm>
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
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace calcpp {

    namespace fexpr {

        // @Function det
        struct det: public FunctionExpression {
            det() : FunctionExpression("det", {arg("m")}) {}
            expression call(expression args) override {
                auto matrix = args->at(0);
                if (matrix == Type::MATRIX && matrix->size() > 0) {
                    if (matrix == Type::COMPLEX) {
                        auto gsl_mat = to_gsl_matrix_complex(matrix);
                        auto gsl_perm = to_gsl_permutation(matrix);
                        int signum;
                        gsl_linalg_complex_LU_decomp(
                            gsl_mat.get(), gsl_perm.get(), &signum);
                        return num(gsl_linalg_complex_LU_det(gsl_mat.get(), signum));
                    } else {
                        auto gsl_mat = to_gsl_matrix(matrix);
                        auto gsl_perm = to_gsl_permutation(matrix);
                        int signum;
                        gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return num(gsl_linalg_LU_det(gsl_mat.get(), signum));
                    }
                }
                THROW_ERROR("det expected a non-empty matrix. Got: " << matrix);
            }
        };

        // @Function lndet
        struct lndet: public FunctionExpression {
            lndet() : FunctionExpression("lndet", {arg("m")}) {}
            expression call(expression args) const override {
                auto matrix = args->at(0);
                if (matrix == Type::MATRIX && matrix->size() > 0) {
                    if (matrix == Type::COMPLEX) {
                        auto gsl_mat = to_gsl_matrix_complex(matrix);
                        auto gsl_perm = to_gsl_permutation(matrix);
                        int signum;
                        gsl_linalg_complex_LU_decomp(
                            gsl_mat.get(), gsl_perm.get(), &signum);
                        return num(gsl_linalg_complex_LU_lndet(gsl_mat.get()));
                    } else {
                        auto gsl_mat = to_gsl_matrix(matrix);
                        auto gsl_perm = to_gsl_permutation(matrix);
                        int signum;
                        gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return num(gsl_linalg_LU_lndet(gsl_mat.get()));
                    }
                }
                THROW_ERROR("lndet expected non-empty matrix. Got: " << matrix);
            }
        };

        // @Function LU
        struct LU: public FunctionExpression {
            LU() : FunctionExpression("LU", {arg("m")}) {}
            expression call(expression args) const override {
                auto matrix = args->at(0);
                if (matrix == Type::MATRIX && matrix->size() > 0) {
                    if (matrix == Type::COMPLEX) {
                        auto gsl_mat = to_gsl_matrix_complex(matrix);
                        auto gsl_perm = to_gsl_permutation(matrix);
                        int signum;
                        gsl_linalg_complex_LU_decomp(
                            gsl_mat.get(), gsl_perm.get(), &signum);
                        return tuple({var("LU", matrix(gsl_mat)),
                                      var("P", matrix(gsl_perm)),
                                      var("sign", num(signum))});
                    } else {
                        auto gsl_mat = to_gsl_matrix(matrix);
                        auto gsl_perm = to_gsl_permutation(matrix);
                        nt signum;
                        gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return tuple({var("LU", matrix(gsl_mat)),
                                      var("P", matrix(gsl_perm)),
                                      var("sign", num(signum))});
                    }
                }
                THROW_ERROR(
                    "LU Factorization expects a non-empty matrix. Got: " << matrix);
            }
        };

        // @Function LUsolve: solve
        struct LUsolve: public FunctionExpression {
            LUsolve() : FunctionExpression("LUsolve", {arg("A"), arg("b")}) {}
            expression call(expression args) const override {
                auto A = args->at(0);
                auto b = args->at(1);
                if (A == Type::MATRIX && b == Type::MATRIX &&
                    (A->shape(0) == b->size())) {
                    if (A == Type::COMPLEX || b == Type::COMPLEX) {
                        auto LU = to_gsl_matrix_complex(A);
                        auto perm = to_gsl_permutation(A);
                        auto x = to_gsl_vector_complex(b);
                        int signum;
                        gsl_linalg_complex_LU_decomp(LU.get(), perm.get(), &signum);
                        gsl_linalg_complex_LU_svx(LU.get(), perm.get(), x.get());
                        return matrix(x);
                    } else {
                        auto LU = to_gsl_matrix(A);
                        auto perm = to_gsl_permutation(A);
                        auto x = to_gsl_vector(b);
                        int signum;
                        gsl_linalg_LU_decomp(LU.get(), perm.get(), &signum);
                        gsl_linalg_LU_svx(LU.get(), perm.get(), x.get());
                        return matrix(x);
                    }
                }
                THROW_ERROR(
                    "Cholesky decomposition expects a non-empty matrix. Got: "
                    << matrix);
            }
        };

        // @Function SVD
        struct SVD: public FunctionExpression {
            SVD() : FunctionExpression("SVD", {arg("m")}) {}
            expression call(expression args) const override {
                auto matrix = args->at(0);
                if (matrix == Type::MATRIX && matrix->size() > 0) {
                    if (matrix == Type::COMPLEX) {
                        THROW_ERROR("Cannot compute SVD of complex matrix");
                    } else {
                        size_t n = matrix->shape(1);
                        auto A = to_gsl_matrix(matrix);
                        auto V = make_gsl_matrix(n, n);
                        auto S = make_gsl_vector(n);
                        auto work = make_gsl_vector(n);
                        int code =
                            gsl_linalg_SV_decomp(A.get(), V.get(), S.get(), work.get());
                        if (code != 0) {
                            THROW_ERROR("SVD failed on matrix: " << matrix);
                        }
                        return tuple({var("U", matrix(A)),
                                      var("S", matrix(S)),
                                      var("V", matrix(V))});
                    }
                }
                THROW_ERROR("SVD expects a non-empty matrix. Got: " << matrix);
            }
        };

        // @Function QR
        struct QR: public FunctionExpression {
            QR() : FunctionExpression("QR", {arg("m")}) {}
            expression call(expression args) const override {
                auto matrix = args->at(0);
                if (matrix == Type::MATRIX && matrix->size() > 0) {
                    if (matrix == Type::COMPLEX) {
                        THROW_ERROR("Cannot compute SVD of complex matrix");
                    } else {
                        size_t m = matrix->shape(0);
                        size_t n = matrix->shape(1);
                        auto QR = to_gsl_matrix(matrix);
                        auto tau = make_gsl_vector(std::min(m, n));
                        int code = gsl_linalg_QR_decomp(QR.get(), tau.get());
                        if (code != 0) {
                            THROW_ERROR(
                                "QR decomposition failed on matrix: " << matrix);
                        }
                        auto Q = make_gsl_matrix(m, m);
                        auto R = make_gsl_matrix(m, n);
                        code =
                            gsl_linalg_QR_unpack(QR.get(), tau.get(), Q.get(), R.get());
                        if (code != 0) {
                            THROW_ERROR(
                                "QR decomposition failed on matrix: " << matrix);
                        }
                        return tuple({
                            var("Q", matrix(Q)),
                            var("R", matrix(R)),
                        });
                    }
                }
                THROW_ERROR(
                    "QR decomposition expects a non-empty matrix. Got: " << matrix);
            }
        };

    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression LU = std::shared_ptr<fexpr::LU>(new fexpr::LU());
        const expression LUsolve = std::shared_ptr<fexpr::LUsolve>(new fexpr::LUsolve());
        const expression QR = std::shared_ptr<fexpr::QR>(new fexpr::QR());
        const expression SVD = std::shared_ptr<fexpr::SVD>(new fexpr::SVD());
        const expression det = std::shared_ptr<fexpr::det>(new fexpr::det());
        const expression lndet = std::shared_ptr<fexpr::lndet>(new fexpr::lndet());
        // end sourcegen
    }  // namespace functions
}  // namespace calcpp
