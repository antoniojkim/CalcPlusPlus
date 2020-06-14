#pragma once

#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/MatrixExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"

namespace Functions {
    // @Function det
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 1){
                auto matrix = args[0]->matrix();
                if (matrix){
                    if (matrix->isComplex()){
                        auto gsl_mat = matrix->to_gsl_matrix_complex();
                        auto gsl_perm = matrix->to_gsl_permutation();
                        int signum;
                        gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return NumExpression::construct(gsl_linalg_complex_LU_det(gsl_mat.get(), signum));
                    }
                    else{
                        auto gsl_mat = matrix->to_gsl_matrix();
                        auto gsl_perm = matrix->to_gsl_permutation();
                        int signum;
                        gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return NumExpression::construct(gsl_linalg_LU_det(gsl_mat.get(), signum));
                    }
                }
            }
            return InvalidExpression::construct(Exception("Determinant expects a matrix expression. Got: ", e));
        }
    } det ("det");

    // @Function lndet
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 1){
                auto matrix = args[0]->matrix();
                if (matrix){
                    if (matrix->isComplex()){
                        auto gsl_mat = matrix->to_gsl_matrix_complex();
                        auto gsl_perm = matrix->to_gsl_permutation();
                        int signum;
                        gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return NumExpression::construct(gsl_linalg_complex_LU_lndet(gsl_mat.get(), signum));
                    }
                    else{
                        auto gsl_mat = matrix->to_gsl_matrix();
                        auto gsl_perm = matrix->to_gsl_permutation();
                        int signum;
                        gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return NumExpression::construct(gsl_linalg_LU_lndet(gsl_mat.get(), signum));
                    }
                }
            }
            return InvalidExpression::construct(Exception("Determinant expects a matrix expression. Got: ", e));
        }
    } lndet ("lndet");

    // @Function LU
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 1){
                auto matrix = args[0]->matrix();
                if (matrix){
                    if (matrix->isComplex()){
                        auto gsl_mat = matrix->to_gsl_matrix_complex();
                        auto gsl_perm = matrix->to_gsl_permutation();
                        int signum;
                        gsl_linalg_complex_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return TupleExpression::construct({
                            MatrixExpression::construct(gsl_mat.get()),
                            MatrixExpression::construct(gsl_perm.get()),
                            NumExpression::construct(signum)
                        });
                    }
                    else{
                        auto gsl_mat = matrix->to_gsl_matrix();
                        auto gsl_perm = matrix->to_gsl_permutation();
                        int signum;
                        gsl_linalg_LU_decomp(gsl_mat.get(), gsl_perm.get(), &signum);
                        return TupleExpression::construct({
                            MatrixExpression::construct(gsl_mat.get()),
                            MatrixExpression::construct(gsl_perm.get()),
                            NumExpression::construct(signum)
                        });
                    }
                }
            }
            return InvalidExpression::construct(Exception("LU Factorization expects a matrix expression. Got: ", e));
        }
    } LU ("LU");

    // @Function LUsolve solve
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 2){
                auto A = args[0]->matrix();
                auto b = args[1]->matrix();
                if (A && b && (A->rows() == b->rows() * b->cols())){
                    if (A->isComplex() || b->isComplex()){
                        auto LU = A->to_gsl_matrix_complex();
                        auto perm = A->to_gsl_permutation();
                        auto x = b->to_gsl_vector_complex();
                        int signum;
                        gsl_linalg_complex_LU_decomp(LU.get(), perm.get(), &signum);
                        gsl_linalg_complex_LU_svx(LU.get(), perm.get(), x.get())
                        return MatrixExpression::construct(x.get());
                    }
                    else{
                        auto LU = A->to_gsl_matrix();
                        auto perm = A->to_gsl_permutation();
                        auto x = b->to_gsl_vector();
                        int signum;
                        gsl_linalg_LU_decomp(LU.get(), perm.get(), &signum);
                        gsl_linalg_LU_svx(LU.get(), perm.get(), x.get())
                        return MatrixExpression::construct(x.get());
                    }
                }
            }
            return InvalidExpression::construct(Exception("LU Solve expects a (m, n) matrix expression and a (n) vector expression. Got: ", e));
        }
    } LUsolve ("LUsolve");

    // @Function Cholesky
    const struct: public NamedFunction {
        expression evaluate(expression e) override {
            ParsedArgs args(e);
            if (args.size() == 1){
                auto matrix = args[0]->matrix();
                if (matrix){
                    if (matrix->isComplex()){
                        auto gsl_mat = matrix->to_gsl_matrix_complex();
                        int code = gsl_linalg_complex_cholesky_decomp(gsl_mat.get());
                        if (code != 0){
                            return InvalidExpression::construct(Exception("Cholesky decomposition expects a positive definite matrix"));
                        }
                        return MatrixExpression::construct(gsl_mat.get());
                    }
                    else{
                        auto gsl_mat = matrix->to_gsl_matrix();
                        int code = gsl_linalg_cholesky_decomp1(gsl_mat.get());
                        if (code != 0){
                            return InvalidExpression::construct(Exception("Cholesky decomposition expects a positive definite matrix"));
                        }
                        return MatrixExpression::construct(gsl_mat.get());
                    }
                }
            }
            return InvalidExpression::construct(Exception("Cholesky decomposition expects a matrix expression. Got: ", e));
        }
    } Cholesky ("Cholesky");
}
