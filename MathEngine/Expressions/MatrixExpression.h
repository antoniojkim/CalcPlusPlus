#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>

#include "Expression.h"

typedef std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> unique_gsl_matrix;
typedef std::unique_ptr<gsl_matrix_complex, decltype(&gsl_matrix_complex_free)> unique_gsl_matrix_complex;
typedef std::unique_ptr<gsl_permutation, decltype(&gsl_permutation_free)> unique_gsl_permutation;

class MatrixExpression: public Expression {
    std::list<expression> mat;
    size_t numRows, numCols;

    MatrixExpression();
    MatrixExpression(std::list<expression>&& matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::initializer_list<double> matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols);
    MatrixExpression(gsl_matrix* matrix);
    MatrixExpression(gsl_matrix_complex* matrix);

    public:

        static expression construct();
        static expression construct(std::list<expression>&& matrix, size_t numRows, size_t numCols);
        static expression construct(std::initializer_list<double> matrix, size_t numRows, size_t numCols);
        static expression construct(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols);
        static expression construct(gsl_matrix* matrix);
        static expression construct(gsl_matrix_complex* matrix);

        std::list<expression>& getMatrix();
        size_t rows() const;
        size_t cols() const;

        inline const MatrixExpression* matrix() const override { return this; }

        expression evaluate(const Variables& vars) override;

        EXPRESSION_OVERRIDES

        unique_gsl_matrix to_gsl_matrix() const;
        unique_gsl_matrix_complex to_gsl_matrix_complex() const;
        unique_gsl_permutation to_gsl_permutation() const;
};

inline unique_gsl_matrix make_gsl_matrix(size_t rows, size_t cols){
    return unique_gsl_matrix(gsl_matrix_alloc(rows, cols), gsl_matrix_free);
}
inline unique_gsl_matrix_complex make_gsl_matrix_complex(size_t rows, size_t cols){
    return unique_gsl_matrix_complex(gsl_matrix_complex_alloc(rows, cols), gsl_matrix_complex_free);
}
inline unique_gsl_permutation make_gsl_permutation(size_t rows){
    return unique_gsl_permutation(gsl_permutation_alloc(rows), gsl_permutation_free);
}
