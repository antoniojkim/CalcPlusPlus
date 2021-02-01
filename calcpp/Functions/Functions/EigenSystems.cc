#include <initializer_list>
#include <list>
#include <utility>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_eigen.h>

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

namespace calpp {

    namespace fexpr {

        typedef std::
            unique_ptr<gsl_eigen_nonsymmv_workspace, decltype(&gsl_eigen_nonsymmv_free)>
                unique_eigen_nonsymmv_workspace;
        unique_eigen_nonsymmv_workspace make_unique_eigen_nonsymmv_workspace(size_t n) {
            return unique_eigen_nonsymmv_workspace(
                gsl_eigen_nonsymmv_alloc(n), gsl_eigen_nonsymmv_free);
        }

        // @Function Eig: eig eigen
        struct Eig: public FunctionExpression {
            Eig() : FunctionExpression("Eig", {arg("m")}) {}
            expression call(expression args) const override {
                auto matrix = args->at(0);
                if (matrix == Type::MATRIX && matrix->size() > 0) {
                    if (matrix->isComplex()) {
                        THROW_ERROR("Cannot compute Eigenvalues and Eigenvectors "
                                    "of complex matrix");
                    }
                    if (matrix->shape(0) != matrix->shape(1)) {
                        THROW_ERROR("Cannot compute Eigenvalues and Eigenvectors "
                                    "of non-square matrix");
                    }
                    size_t n = matrix->shape(0);
                    auto A = to_gsl_matrix(matrix);
                    auto eval = make_gsl_vector_complex(n);
                    auto evec = make_gsl_matrix_complex(n, n);
                    auto w = make_unique_eigen_nonsymmv_workspace(n);
                    int code =
                        gsl_eigen_nonsymmv(A.get(), eval.get(), evec.get(), w.get());
                    if (code != 0) {
                        THROW_ERROR("Failed to compute eigensystem for: " << matrix);
                    }
                    return tuple({
                        var("Λ", matrix(eval)),
                        var("X", matrix(evec)),
                    });
                }
                THROW_ERROR("Eig expects a non-empty matrix. Got: " << matrix);
            }
        };

    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression Eig = std::shared_ptr<fexpr::Eig>(new fexpr::Eig());
        // end sourcegen
    }  // namespace functions
}  // namespace calpp
