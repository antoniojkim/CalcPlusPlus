
#include <list>
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/exceptions.h"
#include "../NumericalExpression.h"
#include "../MatrixExpression.h"

using namespace std;
using namespace Scanner;

MatrixExpression::MatrixExpression(): Expression(MATRIX) {}
MatrixExpression::MatrixExpression(std::vector<expression>&& matrix, size_t rows, size_t cols):
    Expression(MATRIX), mat{std::move(matrix)}, rows{rows}, cols{cols} {
    if (rows*cols != mat.size()){
        throw Exception("Matrix Expression expected ", rows*cols, " elements. Got: ", mat.size());
    }
}
MatrixExpression::MatrixExpression(std::list<expression>& matrix, size_t rows, size_t cols):
    Expression(MATRIX), rows{rows}, cols{cols} {
    if (rows*cols != matrix.size()){
        throw Exception("Matrix Expression expected ", rows*cols, " elements. Got: ", matrix.size());
    }
    mat.reserve(matrix.size());
    for (auto e : matrix){
        mat.emplace_back(e);
    }
}
MatrixExpression::MatrixExpression(std::initializer_list<double> matrix, size_t rows, size_t cols):
    Expression(MATRIX), rows{rows}, cols{cols} {
    if (rows*cols != matrix.size()){
        throw Exception("Matrix Expression expected ", rows*cols, " elements. Got: ", matrix.size());
    }
    mat.reserve(matrix.size());
    for (auto val : matrix){
        mat.emplace_back(NumExpression::construct(val));
    }
}
MatrixExpression::MatrixExpression(std::initializer_list<gsl_complex> matrix, size_t rows, size_t cols):
    Expression(MATRIX), rows{rows}, cols{cols} {
    if (rows*cols != matrix.size()){
        throw Exception("Matrix Expression expected ", rows*cols, " elements. Got: ", matrix.size());
    }
    mat.reserve(matrix.size());
    for (auto val : matrix){
        mat.emplace_back(NumExpression::construct(val));
    }
}
MatrixExpression::MatrixExpression(unique_gsl_matrix& matrix):
    Expression(MATRIX), rows{matrix->size1}, cols{matrix->size2} {
    mat.reserve(rows*cols);
    for (size_t r = 0; r < rows; ++r){
        for (size_t c = 0; c < cols; ++c){
            mat.emplace_back(NumExpression::construct(gsl_matrix_get(matrix.get(), r, c)));
        }
    }
}
MatrixExpression::MatrixExpression(unique_gsl_matrix_complex& matrix):
    Expression(MATRIX), rows{matrix->size1}, cols{matrix->size2} {
    mat.reserve(rows*cols);
    for (size_t r = 0; r < rows; ++r){
        for (size_t c = 0; c < cols; ++c){
            mat.emplace_back(NumExpression::construct(gsl_matrix_complex_get(matrix.get(), r, c)));
        }
    }
}
MatrixExpression::MatrixExpression(unique_gsl_permutation& permutation):
    Expression(MATRIX), rows{1}, cols{permutation->size} {
    mat.reserve(rows*cols);
    for (size_t c = 0; c < cols; ++c){
        mat.emplace_back(NumExpression::construct(gsl_permutation_get(permutation.get(), c)));
    }
}
MatrixExpression::MatrixExpression(unique_gsl_vector& vec):
    Expression(MATRIX), rows{vec->size}, cols{1} {
    mat.reserve(rows);
    for (size_t r = 0; r < rows; ++r){
        mat.emplace_back(NumExpression::construct(gsl_vector_get(vec.get(), r)));
    }
}
MatrixExpression::MatrixExpression(unique_gsl_vector_complex& vec):
    Expression(MATRIX), rows{vec->size}, cols{1} {
    mat.reserve(rows);
    for (size_t r = 0; r < rows; ++r){
        mat.emplace_back(NumExpression::construct(gsl_vector_complex_get(vec.get(), r)));
    }
}


expression MatrixExpression::construct(){
    return shared_ptr<MatrixExpression>(new MatrixExpression());
}
expression MatrixExpression::construct(std::vector<expression>&& matrix, size_t rows, size_t cols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(std::move(matrix), rows, cols));
}
expression MatrixExpression::construct(std::list<expression>& matrix, size_t rows, size_t cols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(matrix, rows, cols));
}
expression MatrixExpression::construct(std::initializer_list<double> matrix, size_t rows, size_t cols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(std::forward<std::initializer_list<double>>(matrix), rows, cols));
}
expression MatrixExpression::construct(std::initializer_list<gsl_complex> matrix, size_t rows, size_t cols){
    return shared_ptr<MatrixExpression>(new MatrixExpression(std::forward<std::initializer_list<gsl_complex>>(matrix), rows, cols));
}
expression MatrixExpression::construct(unique_gsl_matrix& matrix){
    return shared_ptr<MatrixExpression>(new MatrixExpression(matrix));
}
expression MatrixExpression::construct(unique_gsl_matrix_complex& matrix){
    return shared_ptr<MatrixExpression>(new MatrixExpression(matrix));
}
expression MatrixExpression::construct(unique_gsl_permutation& permutation){
    return shared_ptr<MatrixExpression>(new MatrixExpression(permutation));
}
expression MatrixExpression::construct(unique_gsl_vector_complex& vec){
    return shared_ptr<MatrixExpression>(new MatrixExpression(vec));
}
expression MatrixExpression::construct(unique_gsl_vector& vec){
    return shared_ptr<MatrixExpression>(new MatrixExpression(vec));
}

expression MatrixExpression::at(const int index) {
    return mat.at(index);
}
size_t shape(const int axis) const override {
    switch(axis){
        case 0: return rows;
        case 1: return cols;
        default: throw Exception("Axis out of bounds: ", axis);
    }
}
size_t size() const override { return rows*cols; }


expression MatrixExpression::simplify() {
    list<expression> simplified;
    for (auto expr : mat){
        simplified.emplace_back(expr->simplify());
    }
    return MatrixExpression::construct(std::move(simplified), rows, cols);
 }
expression MatrixExpression::derivative(const std::string& var) {
    list<expression> derivatives;
    for (auto expr : mat){
        derivatives.emplace_back(expr->derivative(var));
    }
    return MatrixExpression::construct(std::move(derivatives), rows, cols);
}
expression MatrixExpression::integrate(const std::string& var) {
    list<expression> integrals;
    for (auto expr : mat){
        integrals.emplace_back(expr->integrate(var));
    }
    return MatrixExpression::construct(std::move(integrals), rows, cols);
}


bool MatrixExpression::isComplex() const {
    for(auto& expr: mat){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}
bool MatrixExpression::isEvaluable(const Variables& vars) const {
    for(auto expr : mat){
        if (!expr->isEvaluable()){
            return false;
        }
    }
    return true;
}

expression MatrixExpression::eval(const Variables& vars) {
    vector<expression> evaluated;
    evaluated.reserve(mat.size());
    for (auto expr : mat){
        evaluated.emplace_back(expr->eval(vars));
    }
    return MatrixExpression::construct(std::move(evaluated), rows, cols);
}
double MatrixExpression::value(const Variables& vars) const { return GSL_NAN; }


bool MatrixExpression::equals(expression e, double precision) const {
    if (e->is(MATRIX) && rows == e->shape(0) && cols == e->shape(0)){
        for (size_t i = 0; i < mat.size(); ++i){
            if (!mat.at(i)->equals(e->at(i), precision)){
                return false;
            }
        }
        return true;
    }
    return false;
}

std::ostream& MatrixExpression::print(std::ostream& out, const bool pretty) const {
    if (!mat.empty()){
        if (rows > 1){
            out << "{";
        }
        size_t i = 0;
        for (size_t r = 0; r < rows; ++r){
            if (r != 0){ out << ", "; }
            out << "{";
            for (size_t c = 0; c < cols; ++c){
                if (c != 0){ out << ", "; }
                mat[i++]->print(out, pretty);
            }
            out << "}";
        }
        if (rows > 1){
            out << "}";
        }
    }
    else {
        out << "{}";
    }
    return out;
}
std::ostream& MatrixExpression::postfix(std::ostream& out) const {
    if (!mat.empty()){
        if (rows > 1){
            out << "{";
        }
        size_t i = 0;
        for (size_t r = 0; r < rows; ++r){
            if (r != 0){ out << ", "; }
            out << "{";
            for (size_t c = 0; c < cols; ++c){
                if (c != 0){ out << ", "; }
                mat[i++]->postfix(out);
            }
            out << "}";
        }
        if (rows > 1){
            out << "}";
        }
    }
    else {
        out << "{}";
    }
    return out;
}


unique_gsl_matrix to_gsl_matrix(expression e) const {
    if (e->is(MATRIX)){
        auto gsl_mat = make_gsl_matrix(e->shape(0), e->shape(1));
        size_t i = 0;
        for (size_t r = 0; r < e->shape(0); ++r){
            for (size_t c = 0; c < e->shape(1); ++c){
                gsl_matrix_set(gsl_mat.get(), r, c, e->at(i++)->value());
            }
        }
        return gsl_mat;
    }
    return nullptr;
}
unique_gsl_matrix_complex to_gsl_matrix_complex(expression e) const {
    if (e->is(MATRIX)){
        auto gsl_mat = make_gsl_matrix_complex(e->shape(0), e->shape(1));
        size_t i = 0;
        for (size_t r = 0; r < e->shape(0); ++r){
            for (size_t c = 0; c < e->shape(1); ++c){
                gsl_matrix_complex_set(gsl_mat.get(), r, c, e->at(i++)->complex());
            }
        }
        return gsl_mat;
    }
    return nullptr;
}
unique_gsl_permutation to_gsl_permutation(expression e) const {
    if (e->is(MATRIX)){
        return make_gsl_permutation(e->shape(0));
    }
    return nullptr;
}
unique_gsl_vector to_gsl_vector(expression e) const {
    if (e->is(MATRIX)){
        auto gsl_vec = make_gsl_vector(e->size());
        for (size_t i = 0; i < e->size(); ++i){
            gsl_vector_set(gsl_mat.get(), i, e->at(i)->value());
        }
        return gsl_vec;
    }
    return nullptr;
}
unique_gsl_vector_complex to_gsl_vector_complex(expression e) const {
    if (e->is(MATRIX)){
        auto gsl_vec = make_gsl_vector_complex(e->size());
        for (size_t i = 0; i < e->size(); ++i){
            gsl_vector_complex_set(gsl_mat.get(), i, e->at(i)->complex());
        }
        return gsl_vec;
    }
    return nullptr;
}
