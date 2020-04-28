#pragma once

#include "Expression.h"

expression operator+(const expression expr1, const expression expr2);
expression operator+(double expr1, const expression expr2);
expression operator+(const expression expr1, double expr2);
expression operator+(const gsl_complex& expr1, const expression expr2);
expression operator+(const expression expr1, const gsl_complex& expr2);

expression operator-(const expression expr);
expression operator-(const expression expr1, const expression expr2);
expression operator-(double expr1, const expression expr2);
expression operator-(const expression expr1, double expr2);
expression operator-(const gsl_complex& expr1, const expression expr2);
expression operator-(const expression expr1, const gsl_complex& expr2);

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
