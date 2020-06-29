#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_vector.h>

#include "Expression.h"

#define UNIQUE_GSL(M)                                           \
    typedef std::unique_ptr<M, decltype(&M##_free)> unique_##M; \
    inline unique_##M make_##M(size_t rows, size_t cols){       \
        return unique_##M(M##_alloc(rows, cols), M##_free);     \
    }                                                           \
    unique_##M to_##M(expression e);

UNIQUE_GSL(gsl_matrix)
UNIQUE_GSL(gsl_matrix_complex)

#undef UNIQUE_GSL

#define UNIQUE_GSL(M)                                           \
    typedef std::unique_ptr<M, decltype(&M##_free)> unique_##M; \
    inline unique_##M make_##M(size_t size){                    \
        return unique_##M(M##_alloc(size), M##_free);           \
    }                                                           \
    unique_##M to_##M(expression e);

UNIQUE_GSL(gsl_permutation)
UNIQUE_GSL(gsl_vector)
UNIQUE_GSL(gsl_vector_complex)

#undef UNIQUE_GSL


class MatrixExpression: public Expression {
    std::vector<expression> mat;
    size_t rows, cols;

    MatrixExpression();
    MatrixExpression(std::vector<expression>&& matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::list<expression>& matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::initializer_list<double> matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols);
    MatrixExpression(unique_gsl_matrix& matrix);
    MatrixExpression(unique_gsl_matrix_complex& matrix);
    MatrixExpression(unique_gsl_permutation& permutation);
    MatrixExpression(unique_gsl_vector& vec);
    MatrixExpression(unique_gsl_vector_complex& vec);

    public:

        static expression construct();
        static expression construct(std::vector<expression>&& matrix, size_t numRows, size_t numCols);
        static expression construct(std::list<expression>& matrix, size_t numRows, size_t numCols);
        static expression construct(std::initializer_list<double> matrix, size_t numRows, size_t numCols);
        static expression construct(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols);
        static expression construct(unique_gsl_matrix& matrix);
        static expression construct(unique_gsl_matrix_complex& matrix);
        static expression construct(unique_gsl_permutation& matrix);
        static expression construct(unique_gsl_vector& vec);
        static expression construct(unique_gsl_vector_complex& vec);

        expression at(const int index);
        size_t shape(const int axis) const;
        size_t size() const;

        EXPRESSION_OVERRIDES
};
