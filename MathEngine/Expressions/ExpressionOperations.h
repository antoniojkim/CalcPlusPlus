#pragma once

#include "Expression.h"

expression operator+(expression&& expr1, expression&& expr2);
expression operator+(double expr1, expression&& expr2);
expression operator+(expression&& expr1, double expr2);
expression operator+(const gsl_complex& expr1, expression&& expr2);
expression operator+(expression&& expr1, const gsl_complex& expr2);

expression operator-(expression&& expr1, expression&& expr2);
expression operator-(double expr1, expression&& expr2);
expression operator-(expression&& expr1, double expr2);
expression operator-(const gsl_complex& expr1, expression&& expr2);
expression operator-(expression&& expr1, const gsl_complex& expr2);

expression operator*(expression&& expr1, expression&& expr2);
expression operator*(double expr1, expression&& expr2);
expression operator*(expression&& expr1, double expr2);
expression operator*(const gsl_complex& expr1, expression&& expr2);
expression operator*(expression&& expr1, const gsl_complex& expr2);

expression operator/(expression&& expr1, expression&& expr2);
expression operator/(double expr1, expression&& expr2);
expression operator/(expression&& expr1, double expr2);
expression operator/(const gsl_complex& expr1, expression&& expr2);
expression operator/(expression&& expr1, const gsl_complex& expr2);

expression operator^(expression&& expr1, expression&& expr2);
expression operator^(double expr1, expression&& expr2);
expression operator^(expression&& expr1, double expr2);
expression operator^(const gsl_complex& expr1, expression&& expr2);
expression operator^(expression&& expr1, const gsl_complex& expr2);
