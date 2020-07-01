
#include <iomanip>
#include <memory>
#include <sstream>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../../Utils/Fraction.h"
#include "../../Utils/Numeric.h"
#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"
#include "../VariableExpression.h"

using namespace std;
using namespace Scanner;

NumExpression::NumExpression(double real, double imag):
    NumericalExpression{NUM}, real{real}, imag{imag} {}
NumExpression::NumExpression(const std::string& num):
    NumericalExpression{NUM}, real{0}, imag{0} {
    switch(num.at(0)){
        case 'i':
        case 'j':
            imag = 1;
            return;
        default:
            break;
    }
    istringstream ss {num};
    if (!(ss >> real)){
        throw Exception("Number Error: Invalid Number ", num);
    }
    char i;
    if ((ss >> i) && (i == 'i' || i == 'j')){
        imag = real;
        real = 0;
    }
}

expression NumExpression::construct(double real, double imag){
    return shared_ptr<NumExpression>(new NumExpression(real, imag));
}
expression NumExpression::construct(const gsl_complex& z){
    return shared_ptr<NumExpression>(new NumExpression(GSL_REAL(z), GSL_IMAG(z)));
}
expression NumExpression::construct(const std::string& num){
    return shared_ptr<NumExpression>(new NumExpression(num));
}


bool NumExpression::isComplex() const { return imag != 0; }
bool NumExpression::isEvaluable(const Variables& vars) const {
    return !gsl_isnan(real) && !gsl_isnan(imag);
}

expression NumExpression::eval(const Variables& vars) {
    if (isEvaluable(vars)){ return copy(); }
    throw Exception("Invalid Number: ", copy());
}
double NumExpression::value(const Variables& vars) const { return real; }
gsl_complex NumExpression::complex(const Variables& vars) const { return gsl_complex{real, imag}; }

bool NumExpression::equals(expression e, double precision) const {
    if (e == NUM){
        return compare(complex(), e->complex(), precision) == 0;
    }
    return false;
}

std::ostream& NumExpression::print(std::ostream& out, const bool pretty) const {
    if (!isEvaluable()){
        return out << "NaN";
    }
    if (real == 0 && imag == 0){
        return out << "0";
    }
    if (real != 0){
        if (pretty){
            long numerator, denominator;
            if (to_fraction(real, numerator, denominator) && denominator != 1 &&
                std::abs(numerator) < 1e6 && std::abs(denominator) < 1e6){
                out << numerator << "/" << denominator;
            }
            else {
                out << std::setprecision(16) << real;
            }
        }
        else {
            out << std::setprecision(16) << real;
        }
        if (imag > 0){ out << "+"; }
    }
    if (imag != 0){
        if (pretty){
            long numerator, denominator;
            if (to_fraction(imag, numerator, denominator) && denominator != 1 &&
                std::abs(numerator) < 1e6 && std::abs(denominator) < 1e6){
                return out << numerator << "/" << denominator << "i";
            }
        }
        out << std::setprecision(16) << imag << "i";
    }
    return out;
}

std::ostream& NumExpression::postfix(std::ostream& out) const {
    if (!isEvaluable()){
        return out << "NaN";
    }
    if (real != 0){
        out << std::setprecision(16) << real;
        if (imag > 0){
            out << " " << std::setprecision(16) << imag << "i" << " +";
        }
        else if (imag < 0){
            out << " " << std::setprecision(16) << -imag << "i" << " -";
        }
    }
    else if (imag > 0){
        out << std::setprecision(16) << imag << "i";
    }
    else if (imag < 0){
        out << std::setprecision(16) << imag << "i";
    }
    else{
        out << 0;
    }
    return out;
}
