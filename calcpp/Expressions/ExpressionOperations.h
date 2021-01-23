#pragma once

#include "Expression.h"

namespace calcpp {

    expression operator+(const expression expr1, const expression expr2);
    expression operator+(const Double expr1, const expression expr2);
    expression operator+(const expression expr1, const Double expr2);
    expression operator+(const gsl_complex& expr1, const expression expr2);
    expression operator+(const expression expr1, const gsl_complex& expr2);
    expression operator+(const gsl_complex& c1, const gsl_complex& c2);
    expression operator+(const gsl_complex& c, const Double d);
    expression operator+(const Double d, const gsl_complex& c);

    expression operator-(const expression expr);
    expression operator-(const expression expr1, const expression expr2);
    expression operator-(const Double expr1, const expression expr2);
    expression operator-(const expression expr1, const Double expr2);
    expression operator-(const gsl_complex& expr1, const expression expr2);
    expression operator-(const expression expr1, const gsl_complex& expr2);
    expression operator-(const gsl_complex& c1, const gsl_complex& c2);
    expression operator-(const gsl_complex& c, const Double d);
    expression operator-(const Double d, const gsl_complex& c);

    expression operator*(const expression expr1, const expression expr2);
    expression operator*(const Double expr1, const expression expr2);
    expression operator*(const expression expr1, const Double expr2);
    expression operator*(const gsl_complex& expr1, const expression expr2);
    expression operator*(const expression expr1, const gsl_complex& expr2);
    expression operator*(const gsl_complex& c1, const gsl_complex& c2);
    expression operator*(const gsl_complex& c, const Double d);
    expression operator*(const Double d, const gsl_complex& c);

    expression operator/(const expression expr1, const expression expr2);
    expression operator/(const Double expr1, const expression expr2);
    expression operator/(const expression expr1, const Double expr2);
    expression operator/(const gsl_complex& expr1, const expression expr2);
    expression operator/(const expression expr1, const gsl_complex& expr2);
    expression operator/(const gsl_complex& c1, const gsl_complex& c2);
    expression operator/(const gsl_complex& c, const Double d);
    expression operator/(const Double d, const gsl_complex& c);

    expression operator^(const expression expr1, const expression expr2);
    expression operator^(const Double expr1, const expression expr2);
    expression operator^(const expression expr1, const Double expr2);
    expression operator^(const gsl_complex& expr1, const expression expr2);
    expression operator^(const expression expr1, const gsl_complex& expr2);
    expression operator^(const gsl_complex& c1, const gsl_complex& c2);
    expression operator^(const gsl_complex& c, const Double d);
    expression operator^(const Double d, const gsl_complex& c);

    bool operator==(const expression, const expression);
    bool operator!=(const expression, const expression);

    bool operator==(const expression, Type type);
    bool operator!=(const expression, Type type);

}  // namespace calcpp
