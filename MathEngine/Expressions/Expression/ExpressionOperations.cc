
#include <utility>

#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"

using namespace std;

expression operator+(const expression expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("+", expr1, expr2);
}
expression operator+(double expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("+", NumExpression::construct(expr1), expr2);
}
expression operator+(const expression expr1, double expr2) {
    return BinaryOperatorExpression::construct("+", expr1, NumExpression::construct(expr2));
}
expression operator+(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("+", NumExpression::construct(expr1), expr2);
}
expression operator+(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("+", expr1, NumExpression::construct(expr2));
}

expression operator-(const expression expr){
    return UnaryFunctionExpression::construct("neg", expr);
}
expression operator-(const expression expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("-", expr1, expr2);
}
expression operator-(double expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("-", NumExpression::construct(expr1), expr2);
}
expression operator-(const expression expr1, double expr2) {
    return BinaryOperatorExpression::construct("-", expr1, NumExpression::construct(expr2));
}
expression operator-(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("-", NumExpression::construct(expr1), expr2);
}
expression operator-(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("-", expr1, NumExpression::construct(expr2));
}

expression operator*(const expression expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("*", expr1, expr2);
}
expression operator*(double expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("*", NumExpression::construct(expr1), expr2);
}
expression operator*(const expression expr1, double expr2) {
    return BinaryOperatorExpression::construct("*", expr1, NumExpression::construct(expr2));
}
expression operator*(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("*", NumExpression::construct(expr1), expr2);
}
expression operator*(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("*", expr1, NumExpression::construct(expr2));
}

expression operator/(const expression expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("/", expr1, expr2);
}
expression operator/(double expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("/", NumExpression::construct(expr1), expr2);
}
expression operator/(const expression expr1, double expr2) {
    return BinaryOperatorExpression::construct("/", expr1, NumExpression::construct(expr2));
}
expression operator/(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("/", NumExpression::construct(expr1), expr2);
}
expression operator/(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("/", expr1, NumExpression::construct(expr2));
}

expression operator^(const expression expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("^", expr1, expr2);
}
expression operator^(double expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("^", NumExpression::construct(expr1), expr2);
}
expression operator^(const expression expr1, double expr2) {
    return BinaryOperatorExpression::construct("^", expr1, NumExpression::construct(expr2));
}
expression operator^(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("^", NumExpression::construct(expr1), expr2);
}
expression operator^(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("^", expr1, NumExpression::construct(expr2));
}
