#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace Function {
    // @Function det(m)
    namespace det {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX;
            auto matrix = args.next();
            if (matrix == MATRIX){
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
            throw Exception("det expected matrix. Got: ", matrix);
        }
    }

    // @Function lndet(m)
    namespace lndet {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX;
            auto matrix = args.next();
            if (matrix == MATRIX){
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
            throw Exception("lndet expected matrix. Got: ", matrix);
        }
    }

    // @Function LU(m)
    namespace LU {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX;
            auto matrix = args.next();
            if (matrix == MATRIX){
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return TupleExpression::construct({
                        MatrixExpression::construct(gsl_mat),
                        MatrixExpression::construct(gsl_perm),
                        NumExpression::construct(signum)
                    });
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);
                    auto gsl_perm = to_gsl_permutation(matrix);
                    int signum;
                    gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                    return TupleExpression::construct({
                        MatrixExpression::construct(gsl_mat),
                        MatrixExpression::construct(gsl_perm),
                        NumExpression::construct(signum)
                    });
                }
            }
            throw Exception("LU Factorization expects a matrix. Got: ", matrix);
        }
    }

    // @Function LUsolve(A, b): solve
    namespace LUsolve {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX;
            auto A = args.next();
            auto b = args.next();
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
            throw Exception("LU Solve expects a (m, n) matrix and a (n) vector. Got: ", args);
        }
    }

    // @Function Cholesky(m)
    namespace Cholesky {
        expression eval(Function::Args& args) {
            using Scanner::MATRIX;
            auto matrix = args.next();
            if (matrix == MATRIX){
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
            throw Exception("Cholesky decomposition expects a matrix. Got: ", matrix);
        }
    }
}
