
#include <utility>

#include "../ExpressionFunctions.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"
#include "../../Scanner/scanner.h"

using namespace std;
using namespace Scanner;

expression operator+(const expression expr1, const expression expr2) {
    if (expr1->evaluable()){
        return expr2 + expr1->value();
    }
    if (expr2->evaluable()){
        return expr1 + expr2->value();
    }
    return OperatorExpression::construct(PLUS, expr1, expr2);
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
    return OperatorExpression::construct(PLUS, expr1, NumExpression::construct(expr2));
}
expression operator+(const gsl_complex& expr1, const expression expr2) {
    return OperatorExpression::construct(PLUS, NumExpression::construct(expr1), expr2);
}
expression operator+(const expression expr1, const gsl_complex& expr2) {
    return OperatorExpression::construct(PLUS, expr1, NumExpression::construct(expr2));
}

expression operator-(const expression expr){
    if (expr->evaluable()){
        return NumExpression::construct(-expr->value());
    }
    return FunctionExpression::construct("neg", expr);
}
expression operator-(const expression expr1, const expression expr2) {
    if (expr1->evaluable() && expr2->evaluable()){
        return NumExpression::construct(expr1->value() - expr2->value());
    }
    return OperatorExpression::construct(MINUS, expr1, expr2);
}
expression operator-(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(expr1 - expr2->value());
    }
    return OperatorExpression::construct(MINUS, NumExpression::construct(expr1), expr2);
}
expression operator-(const expression expr1, double expr2) {
    if (expr1->evaluable()){
        return NumExpression::construct(expr1->value() - expr2);
    }
    return OperatorExpression::construct(MINUS, expr1, NumExpression::construct(expr2));
}
expression operator-(const gsl_complex& expr1, const expression expr2) {
    return OperatorExpression::construct(MINUS, NumExpression::construct(expr1), expr2);
}
expression operator-(const expression expr1, const gsl_complex& expr2) {
    return OperatorExpression::construct(MINUS, expr1, NumExpression::construct(expr2));
}

expression operator*(const expression expr1, const expression expr2) {
    if (expr1->evaluable()){
        return expr1->value() * expr2;
    }
    if (expr2->evaluable()){
        return expr2->value() * expr1;
    }
    return OperatorExpression::construct(STAR, expr1, expr2);
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
    return OperatorExpression::construct(STAR, NumExpression::construct(expr1), expr2);
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
    return OperatorExpression::construct(STAR, NumExpression::construct(expr1), expr2);
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
    return OperatorExpression::construct(STAR, expr1, NumExpression::construct(expr2));
}

expression operator/(const expression expr1, const expression expr2) {
    if (expr1->evaluable() && expr2->evaluable()){
        return NumExpression::construct(expr1->value() / expr2->value());
    }
    return OperatorExpression::construct(SLASH, expr1, expr2);
}
expression operator/(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(expr1 / expr2->value());
    }
    return OperatorExpression::construct(SLASH, NumExpression::construct(expr1), expr2);
}
expression operator/(const expression expr1, double expr2) {
    if (expr1->evaluable()){
        return NumExpression::construct(expr1->value() / expr2);
    }
    return OperatorExpression::construct(SLASH, expr1, NumExpression::construct(expr2));
}
expression operator/(const gsl_complex& expr1, const expression expr2) {
    return OperatorExpression::construct(SLASH, NumExpression::construct(expr1), expr2);
}
expression operator/(const expression expr1, const gsl_complex& expr2) {
    return OperatorExpression::construct(SLASH, expr1, NumExpression::construct(expr2));
}

expression operator^(const expression expr1, const expression expr2) {
    if (expr1->evaluable()){
        return expr1->value() ^ expr2;
    }
    else if (expr2->evaluable()){
        return expr1 ^ expr2->value();
    }
    return OperatorExpression::construct(CARET, expr1, expr2);
}
expression operator^(double expr1, const expression expr2) {
    if (expr2->evaluable()){
        return NumExpression::construct(pow(expr1, expr2->value()));
    }
    if (expr1 == 1){
        return NumExpression::construct(1);
    }
    if (expr1 == 2){
        return FunctionExpression::construct("exp2", expr2);
    }
    return OperatorExpression::construct(CARET, NumExpression::construct(expr1), expr2);
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
    return OperatorExpression::construct(CARET, expr1, NumExpression::construct(expr2));
}
expression operator^(const gsl_complex& expr1, const expression expr2) {
    return OperatorExpression::construct(CARET, NumExpression::construct(expr1), expr2);
}
expression operator^(const expression expr1, const gsl_complex& expr2) {
    return OperatorExpression::construct(CARET, expr1, NumExpression::construct(expr2));
}
