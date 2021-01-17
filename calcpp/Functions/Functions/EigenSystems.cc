#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_eigen.h>

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

    typedef std::unique_ptr<gsl_eigen_nonsymmv_workspace, decltype(&gsl_eigen_nonsymmv_free)> unique_eigen_nonsymmv_workspace;
    unique_eigen_nonsymmv_workspace make_unique_eigen_nonsymmv_workspace(size_t n){
        return unique_eigen_nonsymmv_workspace(gsl_eigen_nonsymmv_alloc(n), gsl_eigen_nonsymmv_free);
    }

    // @Function Eig: eig eigen
    struct Eig: public FunctionExpression {
        Eig(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {{"m", Empty}}) {}  // Signature: (m)
        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::MATRIX;
            auto matrix = arg->at(0)->eval(vars);
            if (matrix == MATRIX && matrix->size() > 0){
                if (matrix->isComplex()){
                    throw Exception("Cannot compute Eigenvalues and Eigenvectors of complex matrix");
                }
                if (matrix->shape(0) != matrix->shape(1)){
                    throw Exception("Cannot compute Eigenvalues and Eigenvectors of non-square matrix");
                }
                size_t n = matrix->shape(0);
                auto A = to_gsl_matrix(matrix);
                auto eval = make_gsl_vector_complex(n);
                auto evec = make_gsl_matrix_complex(n, n);
                auto w = make_unique_eigen_nonsymmv_workspace(n);
                int code = gsl_eigen_nonsymmv(A.get(), eval.get(), evec.get(), w.get());
                if (code != 0){
                    throw Exception("Failed to compute eigensystem for: ", matrix);
                }
                return TupleExpression::construct({
                    VariableExpression::construct("Λ", MatrixExpression::construct(eval)),
                    VariableExpression::construct("X", MatrixExpression::construct(evec)),
                });
            }
            throw Exception("Eig expects a non-empty matrix. Got: ", matrix);
        }
        double value(const Variables& vars = emptyVars) const override { return GSL_NAN; }
    };
    MAKE_FUNCTION_EXPRESSION(Eig)
}
