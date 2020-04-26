
#include <utility>

#include "../NumericalExpression.h"
#include "../ExpressionOperations.h"
#include "../OperatorExpression.h"

using namespace std;

expression operator+(expression&& expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("+", std::move(expr1), std::move(expr2));
}
expression operator+(double expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("+", NumExpression::construct(expr1), std::move(expr2));
}
expression operator+(expression&& expr1, double expr2) {
    return BinaryOperatorExpression::construct("+", std::move(expr1), NumExpression::construct(expr2));
}
expression operator+(const gsl_complex& expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("+", NumExpression::construct(expr1), std::move(expr2));
}
expression operator+(expression&& expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("+", std::move(expr1), NumExpression::construct(expr2));
}

expression operator-(expression&& expr1, expression&&expr2) {
    return BinaryOperatorExpression::construct("-", std::move(expr1), std::move(expr2));
}
expression operator-(double expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("-", NumExpression::construct(expr1), std::move(expr2));
}
expression operator-(expression&& expr1, double expr2) {
    return BinaryOperatorExpression::construct("-", std::move(expr1), NumExpression::construct(expr2));
}
expression operator-(const gsl_complex& expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("-", NumExpression::construct(expr1), std::move(expr2));
}
expression operator-(expression&& expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("-", std::move(expr1), NumExpression::construct(expr2));
}

expression operator*(expression&& expr1, expression&&expr2) {
    return BinaryOperatorExpression::construct("*", std::move(expr1), std::move(expr2));
}
expression operator*(double expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("*", NumExpression::construct(expr1), std::move(expr2));
}
expression operator*(expression&& expr1, double expr2) {
    return BinaryOperatorExpression::construct("*", std::move(expr1), NumExpression::construct(expr2));
}
expression operator*(const gsl_complex& expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("*", NumExpression::construct(expr1), std::move(expr2));
}
expression operator*(expression&& expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("*", std::move(expr1), NumExpression::construct(expr2));
}

expression operator/(expression&& expr1, expression&&expr2) {
    return BinaryOperatorExpression::construct("/", std::move(expr1), std::move(expr2));
}
expression operator/(double expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("/", NumExpression::construct(expr1), std::move(expr2));
}
expression operator/(expression&& expr1, double expr2) {
    return BinaryOperatorExpression::construct("/", std::move(expr1), NumExpression::construct(expr2));
}
expression operator/(const gsl_complex& expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("/", NumExpression::construct(expr1), std::move(expr2));
}
expression operator/(expression&& expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("/", std::move(expr1), NumExpression::construct(expr2));
}

expression operator^(expression&& expr1, expression&&expr2) {
    return BinaryOperatorExpression::construct("^", std::move(expr1), std::move(expr2));
}
expression operator^(double expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("^", NumExpression::construct(expr1), std::move(expr2));
}
expression operator^(expression&& expr1, double expr2) {
    return BinaryOperatorExpression::construct("^", std::move(expr1), NumExpression::construct(expr2));
}
expression operator^(const gsl_complex& expr1, expression&& expr2) {
    return BinaryOperatorExpression::construct("^", NumExpression::construct(expr1), std::move(expr2));
}
expression operator^(expression&& expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("^", std::move(expr1), NumExpression::construct(expr2));
}
