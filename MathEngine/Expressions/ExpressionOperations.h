#pragma once

#include "Expression.h"

expression operator+(const expression expr1, const expression expr2);
expression operator+(double expr1, const expression expr2);
expression operator+(const expression expr1, double expr2);
expression operator+(const gsl_complex& expr1, const expression expr2);
expression operator+(const expression expr1, const gsl_complex& expr2);
expression operator+(const gsl_complex& c1, const gsl_complex& c2);
expression operator+(const gsl_complex& c, double d);
expression operator+(double d, const gsl_complex& c);

expression operator-(const expression expr);
expression operator-(const expression expr1, const expression expr2);
expression operator-(double expr1, const expression expr2);
expression operator-(const expression expr1, double expr2);
expression operator-(const gsl_complex& expr1, const expression expr2);
expression operator-(const expression expr1, const gsl_complex& expr2);
expression operator-(const gsl_complex& c1, const gsl_complex& c2);
expression operator-(const gsl_complex& c, double d);
expression operator-(double d, const gsl_complex& c);

expression operator*(const expression expr1, const expression expr2);
expression operator*(double expr1, const expression expr2);
expression operator*(const expression expr1, double expr2);
expression operator*(const gsl_complex& expr1, const expression expr2);
expression operator*(const expression expr1, const gsl_complex& expr2);

expression operator/(const expression expr1, const expression expr2);
expression operator/(double expr1, const expression expr2);
expression operator/(const expression expr1, double expr2);
expression operator/(const gsl_complex& expr1, const expression expr2);
expression operator/(const expression expr1, const gsl_complex& expr2);

expression operator^(const expression expr1, const expression expr2);
expression operator^(double expr1, const expression expr2);
expression operator^(const expression expr1, double expr2);
expression operator^(const gsl_complex& expr1, const expression expr2);
expression operator^(const expression expr1, const gsl_complex& expr2);

bool operator==(const expression, const expression);
bool operator!=(const expression, const expression);

bool operator==(const expression, Scanner::Type kind);
bool operator!=(const expression, Scanner::Type kind);
