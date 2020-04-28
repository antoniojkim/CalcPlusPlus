
#include <utility>

#include "../ExpressionFunctions.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"

using namespace std;

expression operator+(const expression expr1, const expression expr2) {
    if (expr1->evaluable()){
        return expr2 + expr1->value();
    }
    if (expr2->evaluable()){
        return expr1 + expr2->value();
    }
    return BinaryOperatorExpression::construct("+", expr1, expr2);
}
expression operator+(double expr1, const expression expr2) {
    return expr2 + expr1;
}
expression operator+(const expression expr1, double expr2) {
    if (expr1->evaluable()){
        return NumExpression::construct(expr1->value() + expr2);
    }
    if (expr2 == 0){
        return expr1;
    }
    return BinaryOperatorExpression::construct("+", expr1, NumExpression::construct(expr2));
}
expression operator+(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("+", NumExpression::construct(expr1), expr2);
}
expression operator+(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("+", expr1, NumExpression::construct(expr2));
}

expression operator-(const expression expr){
    if (expr->evaluable()){
        return NumExpression::construct(-expr->value());
    }
    return UnaryFunctionExpression::construct("neg", expr);
}
expression operator-(const expression expr1, const expression expr2) {
    if (expr1->evaluable() && expr2->evaluable()){
        return NumExpression::construct(expr1->value() - expr2->value());
    }
    return BinaryOperatorExpression::construct("-", expr1, expr2);
}
expression operator-(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(expr1 - expr2->value());
    }
    return BinaryOperatorExpression::construct("-", NumExpression::construct(expr1), expr2);
}
expression operator-(const expression expr1, double expr2) {
    if (expr1->evaluable()){
        return NumExpression::construct(expr1->value() - expr2);
    }
    return BinaryOperatorExpression::construct("-", expr1, NumExpression::construct(expr2));
}
expression operator-(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("-", NumExpression::construct(expr1), expr2);
}
expression operator-(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("-", expr1, NumExpression::construct(expr2));
}

expression operator*(const expression expr1, const expression expr2) {
    if (expr1->evaluable()){
        return expr1->value() * expr2;
    }
    if (expr2->evaluable()){
        return expr2->value() * expr1;
    }
    return BinaryOperatorExpression::construct("*", expr1, expr2);
}
expression operator*(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(expr1 * expr2->value());
    }
    if (expr1 == 1){
        return expr2;
    }
    if (expr1 == 0){
        return NumExpression::construct(0);
    }
    return BinaryOperatorExpression::construct("*", NumExpression::construct(expr1), expr2);
}
expression operator*(const expression expr1, double expr2) {
    return expr2 * expr1;
}
expression operator*(const gsl_complex& expr1, const expression expr2) {
    if (GSL_IMAG(expr1) == 0){
        if (GSL_REAL(expr1) == 1){
            return expr2;
        }
        if (GSL_REAL(expr1) == 0){
            return NumExpression::construct(0);
        }
    }
    return BinaryOperatorExpression::construct("*", NumExpression::construct(expr1), expr2);
}
expression operator*(const expression expr1, const gsl_complex& expr2) {
    if (GSL_IMAG(expr2) == 0){
        if (GSL_REAL(expr2) == 1){
            return expr1;
        }
        if (GSL_REAL(expr2) == 0){
            return NumExpression::construct(0);
        }
    }
    return BinaryOperatorExpression::construct("*", expr1, NumExpression::construct(expr2));
}

expression operator/(const expression expr1, const expression expr2) {
    if (expr1->evaluable() && expr2->evaluable()){
        return NumExpression::construct(expr1->value() / expr2->value());
    }
    return BinaryOperatorExpression::construct("/", expr1, expr2);
}
expression operator/(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(expr1 / expr2->value());
    }
    return BinaryOperatorExpression::construct("/", NumExpression::construct(expr1), expr2);
}
expression operator/(const expression expr1, double expr2) {
    if (expr1->evaluable()){
        return NumExpression::construct(expr1->value() / expr2);
    }
    return BinaryOperatorExpression::construct("/", expr1, NumExpression::construct(expr2));
}
expression operator/(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("/", NumExpression::construct(expr1), expr2);
}
expression operator/(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("/", expr1, NumExpression::construct(expr2));
}

expression operator^(const expression expr1, const expression expr2) {
    if (expr1->evaluable()){
        return expr1->value() ^ expr2;
    }
    else if (expr2->evaluable()){
        return expr1 ^ expr2->value();
    }
    return BinaryOperatorExpression::construct("^", expr1, expr2);
}
expression operator^(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(pow(expr1, expr2->value()));
    }
    if (expr1 == 1){
        return NumExpression::construct(1);
    }
    if (expr1 == 2){
        return UnaryFunctionExpression::construct("exp2", expr2);
    }
    return BinaryOperatorExpression::construct("^", NumExpression::construct(expr1), expr2);
}
expression operator^(const expression expr1, double expr2) {
    if (expr1->evaluable()){
        return NumExpression::construct(pow(expr1->value(), expr2));
    }
    if (expr2 == 0){
        return NumExpression::construct(1);
    }
    if (expr2 == 1){
        return expr1;
    }
    if (expr2 == 2){
        return sqr(expr1);
    }
    if (expr2 == 3){
        return cb(expr1);
    }
    return BinaryOperatorExpression::construct("^", expr1, NumExpression::construct(expr2));
}
expression operator^(const gsl_complex& expr1, const expression expr2) {
    return BinaryOperatorExpression::construct("^", NumExpression::construct(expr1), expr2);
}
expression operator^(const expression expr1, const gsl_complex& expr2) {
    return BinaryOperatorExpression::construct("^", expr1, NumExpression::construct(expr2));
}
