
#include <list>
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../NumericalExpression.h"
#include "../MatrixExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

MatrixExpression::MatrixExpression(){}
MatrixExpression::MatrixExpression(std::list<expression>&& matrix, size_t numRows, size_t numCols):
    mat{std::move(matrix)}, numRows{numRows}, numCols{numCols} {
    if (numRows*numCols != mat.size()){
        throw Exception("Matrix Expression expected ", numRows*numCols, " elements. Got: ", mat.size());
    }
}
MatrixExpression::MatrixExpression(std::initializer_list<double> matrix, size_t numRows, size_t numCols):
    numRows{numRows}, numCols{numCols} {
    if (numRows*numCols != matrix.size()){
        throw Exception("Matrix Expression expected ", numRows*numCols, " elements. Got: ", matrix.size());
    }
    for (auto val : matrix){
        mat.emplace_back(NumExpression::construct(val));
    }
}
MatrixExpression::MatrixExpression(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols):
    numRows{numRows}, numCols{numCols} {
    if (numRows*numCols != matrix.size()){
        throw Exception("Matrix Expression expected ", numRows*numCols, " elements. Got: ", matrix.size());
    }
    for (auto val : matrix){
        mat.emplace_back(NumExpression::construct(val));
    }
}
MatrixExpression::MatrixExpression(gsl_matrix* matrix):
    numRows{matrix->size1}, numCols{matrix->size2} {

    for (size_t r = 0; r < numRows; ++r){
        for (size_t c = 0; c < numCols; ++c){
            mat.emplace_back(NumExpression::construct(gsl_matrix_get(matrix, r, c)));
        }
    }
}
MatrixExpression::MatrixExpression(gsl_matrix_complex* matrix):
    numRows{matrix->size1}, numCols{matrix->size2} {

    for (size_t r = 0; r < numRows; ++r){
        for (size_t c = 0; c < numCols; ++c){
            mat.emplace_back(NumExpression::construct(gsl_matrix_complex_get(matrix, r, c)));
        }
    }
}
MatrixExpression::MatrixExpression(gsl_permutation* permutation):
    numRows{1}, numCols{permutation->size} {
    for (size_t c = 0; c < numCols; ++c){
        mat.emplace_back(NumExpression::construct(gsl_permutation_get(permutation, c)));
    }
}


expression MatrixExpression::construct(){
    return shared_ptr<MatrixExpression>(new MatrixExpression());
}
expression MatrixExpression::construct(std::list<expression>&& matrix, size_t numRows, size_t numCols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(std::move(matrix), numRows, numCols));
}
expression MatrixExpression::construct(std::initializer_list<double> matrix, size_t numRows, size_t numCols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(std::forward<std::initializer_list<double>>(matrix), numRows, numCols));
}
expression MatrixExpression::construct(std::initializer_list<gsl_complex> matrix, size_t numRows, size_t numCols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(std::forward<std::initializer_list<gsl_complex>>(matrix), numRows, numCols));
}
expression MatrixExpression::construct(gsl_matrix* matrix){
    return shared_ptr<MatrixExpression>(new MatrixExpression(matrix));
}
expression MatrixExpression::construct(gsl_matrix_complex* matrix){
    return shared_ptr<MatrixExpression>(new MatrixExpression(matrix));
}
expression MatrixExpression::construct(gsl_permutation* permutation){
    return shared_ptr<MatrixExpression>(new MatrixExpression(permutation));
}


const std::list<expression>& MatrixExpression::getMatrix() const { return mat; }
size_t MatrixExpression::rows() const { return numRows; }
size_t MatrixExpression::cols() const { return numCols; }


expression MatrixExpression::simplify() { return copy(); }
expression MatrixExpression::derivative(const std::string& var) {
    list<expression> derivatives;
    for (auto& expr : mat){
        derivatives.emplace_back(expr->derivative(var));
    }
    return MatrixExpression::construct(std::move(derivatives), numRows, numCols);
}
expression MatrixExpression::integrate(const std::string& var) {
    list<expression> integrals;
    for (auto& expr : mat){
        integrals.emplace_back(expr->integrate(var));
    }
    return MatrixExpression::construct(std::move(integrals), numRows, numCols);
}

bool MatrixExpression::evaluable() const {
    for(auto& expr: mat){
        if (!expr->evaluable()){
            return false;
        }
    }
    return true;
}

expression MatrixExpression::evaluate(const Variables& vars) {
    list<expression> evaluated;
    for (auto& expr : mat){
        evaluated.emplace_back(expr->evaluate(vars));
    }
    return MatrixExpression::construct(std::move(evaluated), numRows, numCols);
}

double MatrixExpression::value(const Variables& vars) const { return GSL_NAN; }

bool MatrixExpression::isComplex() const {
    for(auto& expr: mat){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}

std::ostream& MatrixExpression::print(std::ostream& out) const {
    out << "{";
    if (!mat.empty()){
        auto expr = mat.begin();
        for (size_t r = 0; r < numRows; ++r){
            if (r != 0){ out << ", "; }
            out << "{";
            for (size_t c = 0; c < numCols; ++c){
                if (c != 0){ out << ", "; }
                (*(expr++))->print(out);
            }
            out << "}";
        }
    }
    return out << "}";
}
std::ostream& MatrixExpression::postfix(std::ostream& out) const {
    for (auto& expr: mat){
        expr->postfix(out) << " ";
    }
    return out << "matrix_" << numRows << "x" << numCols;
}


unique_gsl_matrix MatrixExpression::to_gsl_matrix() const {
    auto gsl_mat = make_gsl_matrix(numRows, numCols);
    auto expr = mat.begin();
    for (size_t r = 0; r < numRows; ++r){
        for (size_t c = 0; c < numCols; ++c){
            gsl_matrix_set(gsl_mat.get(), r, c, (*(expr++))->value());
        }
    }
    return gsl_mat;
}
unique_gsl_matrix_complex MatrixExpression::to_gsl_matrix_complex() const {
    auto gsl_mat = make_gsl_matrix_complex(numRows, numCols);
    auto expr = mat.begin();
    for (size_t r = 0; r < numRows; ++r){
        for (size_t c = 0; c < numCols; ++c){
            gsl_matrix_complex_set(gsl_mat.get(), r, c, (*(expr++))->complex());
        }
    }
    return gsl_mat;
}
unique_gsl_permutation MatrixExpression::to_gsl_permutation() const {
    return make_gsl_permutation(numRows);
}
