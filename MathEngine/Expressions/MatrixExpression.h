#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"

class MatrixExpression: public Expression {
    std::list<expression> mat;
    size_t numRows, numCols;
  
  public:

    MatrixExpression();
    MatrixExpression(std::list<expression>&& matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::initializer_list<double> matrix, size_t numRows, size_t numCols);
    MatrixExpression(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols);

    std::list<expression>& getMatrix();
    size_t rows();
    size_t cols();

    inline MatrixExpression* matrix() override { return this; }

    EXPRESSION_OVERRIDES

};
