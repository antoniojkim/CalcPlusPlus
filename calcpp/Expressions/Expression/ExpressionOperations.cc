
#include <utility>

#include <gsl/gsl_complex_math.h>

#include "../../Functions/Functions.h"
#include "../../Scanner/scanner.h"
#include "../ExpressionFunctions.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"

using namespace std;
using namespace Scanner;
using namespace ExpressionMath;

constexpr const int addIndex = Functions::indexOf("+");
constexpr const int subIndex = Functions::indexOf("-");
constexpr const int mulIndex = Functions::indexOf("*");
constexpr const int divIndex = Functions::indexOf("/");
constexpr const int powIndex = Functions::indexOf("^");

expression operator+(const expression expr1, const expression expr2) {
    if (expr1->isNumber()){
        if (expr1->isComplex()){
            return expr1->complex() + expr2;
        }
        return expr1->value() + expr2;
    }
    if (expr2->isNumber()){
        if (expr2->isComplex()){
            return expr1 + expr2->complex();
        }
        return expr1 + expr2->value();
    }
    return FunctionExpression::construct(addIndex, {expr1, expr2});
}
expression operator+(double expr1, const expression expr2) {
    return expr2 + expr1;
}
expression operator+(const expression expr1, double expr2) {
    if (expr1->isNumber()){
        if (expr1->isComplex()){
            return expr1->complex() + expr2;
        }
        return NumExpression::construct(expr1->value() + expr2);
    }
    if (expr2 == 0){
        return expr1;
    }
    return FunctionExpression::construct(addIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator+(const gsl_complex& expr1, const expression expr2) {
    if (expr2->isNumber()){
        if (expr2->isComplex()){
            return expr1 + expr2->complex();
        }
        return expr1 + expr2->value();
    }
    return FunctionExpression::construct(addIndex, {NumExpression::construct(expr1), expr2});
}
expression operator+(const expression expr1, const gsl_complex& expr2) {
    return expr2 + expr1;
}
expression operator+(const gsl_complex& c1, const gsl_complex& c2) {
    return NumExpression::construct(gsl_complex_add(c1, c2));
}
expression operator+(const gsl_complex& c, double d){
    return NumExpression::construct(gsl_complex_add(c, {d, 0}));
}
expression operator+(double d, const gsl_complex& c){
    return c + d;
}

expression operator-(const expression expr){
    if (expr->isNumber()){
        return NumExpression::construct(gsl_complex_negative(expr->complex()));
    }
    return FunctionExpression::construct("neg", expr);
}
expression operator-(const expression expr1, const expression expr2) {
    if (expr1->isNumber()){
        if (expr1->isComplex()){
            return expr1->complex() - expr2;
        }
        return expr1->value() - expr2;
    }
    if (expr2->isNumber()){
        if (expr2->isComplex()){
            return expr1 - expr2->complex();
        }
        return expr1 - expr2->value();
    }
    return FunctionExpression::construct(subIndex, {expr1, expr2});
}
expression operator-(double expr1, const expression expr2) {
    if (expr2->isNumber()){
        if (expr2->isComplex()){
            return expr1 - expr2->complex();
        }
        return NumExpression::construct(expr1 - expr2->value());
    }
    return FunctionExpression::construct(subIndex, {NumExpression::construct(expr1), expr2});
}
expression operator-(const expression expr1, double expr2) {
    if (expr1->isNumber()){
        if (expr1->isComplex()){
            return expr1->complex() - expr2;
        }
        return NumExpression::construct(expr1->value() - expr2);
    }
    return FunctionExpression::construct(subIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator-(const gsl_complex& expr1, const expression expr2) {
    if (expr2->isComplex()){
        return expr1 - expr2->complex();
    }
    return FunctionExpression::construct(subIndex, {NumExpression::construct(expr1), expr2});
}
expression operator-(const expression expr1, const gsl_complex& expr2) {
    if (expr1->isComplex()){
        return expr1->complex() - expr2;
    }
    return FunctionExpression::construct(subIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator-(const gsl_complex& c1, const gsl_complex& c2){
    return NumExpression::construct(gsl_complex_sub(c1, c2));
}
expression operator-(const gsl_complex& c, double d){
    return NumExpression::construct(gsl_complex_sub(c, {d, 0}));
}
expression operator-(double d, const gsl_complex& c){
    return NumExpression::construct(gsl_complex_sub({d, 0}, c));
}

expression operator*(const expression expr1, const expression expr2) {
    if (expr1->isNumber()){
        if (expr1->isComplex()){
            return expr1->complex() * expr2;
        }
        return expr1->value() * expr2;
    }
    if (expr2->isNumber()){
        if (expr2->isComplex()){
            return expr1 * expr2->complex();
        }
        return expr2->value() * expr1;
    }
    return FunctionExpression::construct(mulIndex, {expr1, expr2});
}
expression operator*(double expr1, const expression expr2) {
    if (expr2->isNumber()){
        return NumExpression::construct(expr1 * expr2->value());
    }
    if (expr1 == 1){
        return expr2;
    }
    if (expr1 == 0){
        return NumExpression::construct(0);
    }
    return FunctionExpression::construct(mulIndex, {NumExpression::construct(expr1), expr2});
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
    return FunctionExpression::construct(mulIndex, {NumExpression::construct(expr1), expr2});
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
    return FunctionExpression::construct(mulIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator*(const gsl_complex& c1, const gsl_complex& c2){
    return NumExpression::construct(gsl_complex_mul(c1, c2));
}
expression operator*(double d, const gsl_complex& c){
    return NumExpression::construct(gsl_complex_mul({d, 0}, c));
}
expression operator*(const gsl_complex& c, double d){
    return NumExpression::construct(gsl_complex_mul(c, {d, 0}));
}

expression operator/(const expression expr1, const expression expr2) {
    if (expr1->isNumber() && expr2->isNumber()){
        return NumExpression::construct(expr1->value() / expr2->value());
    }
    return FunctionExpression::construct(divIndex, {expr1, expr2});
}
expression operator/(double expr1, const expression expr2) {
    if (expr2->isNumber()){
        return NumExpression::construct(expr1 / expr2->value());
    }
    return FunctionExpression::construct(divIndex, {NumExpression::construct(expr1), expr2});
}
expression operator/(const expression expr1, double expr2) {
    if (expr1->isNumber()){
        return NumExpression::construct(expr1->value() / expr2);
    }
    return FunctionExpression::construct(divIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator/(const gsl_complex& expr1, const expression expr2) {
    return FunctionExpression::construct(divIndex, {NumExpression::construct(expr1), expr2});
}
expression operator/(const expression expr1, const gsl_complex& expr2) {
    return FunctionExpression::construct(divIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator/(const gsl_complex& c1, const gsl_complex& c2){
    return NumExpression::construct(gsl_complex_div(c1, c2));
}
expression operator/(double d, const gsl_complex& c){
    return NumExpression::construct(gsl_complex_div({d, 0}, c));
}
expression operator/(const gsl_complex& c, double d){
    return NumExpression::construct(gsl_complex_div(c, {d, 0}));
}

expression operator^(const expression expr1, const expression expr2) {
    if (expr1->isNumber()){
        return expr1->value() ^ expr2;
    }
    else if (expr2->isNumber()){
        return expr1 ^ expr2->value();
    }
    return FunctionExpression::construct(powIndex, {expr1, expr2});
}
expression operator^(double expr1, const expression expr2) {
    if (expr2->isNumber()){
        return NumExpression::construct(pow(expr1, expr2->value()));
    }
    if (expr1 == 1){
        return NumExpression::construct(1);
    }
    if (expr1 == 2){
        return FunctionExpression::construct("exp2", expr2);
    }
    return FunctionExpression::construct(powIndex, {NumExpression::construct(expr1), expr2});
}
expression operator^(const expression expr1, double expr2) {
    if (expr1->isNumber()){
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
    return FunctionExpression::construct(powIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator^(const gsl_complex& expr1, const expression expr2) {
    return FunctionExpression::construct(powIndex, {NumExpression::construct(expr1), expr2});
}
expression operator^(const expression expr1, const gsl_complex& expr2) {
    return FunctionExpression::construct(powIndex, {expr1, NumExpression::construct(expr2)});
}
expression operator^(const gsl_complex& c1, const gsl_complex& c2){
    return NumExpression::construct(gsl_complex_pow(c1, c2));
}
expression operator^(double d, const gsl_complex& c){
    return NumExpression::construct(gsl_complex_pow({d, 0}, c));
}
expression operator^(const gsl_complex& c, double d){
    return NumExpression::construct(gsl_complex_pow(c, {d, 0}));
}

bool operator==(const expression e1, const expression e2){
    return e1->equals(e2);
}
bool operator!=(const expression e1, const expression e2){
    return !e1->equals(e2);
}

bool operator==(const expression e, Type kind){
    return e && e->is(kind);
}
bool operator!=(const expression e, Type kind){
    return !(e && e->is(kind));
}
