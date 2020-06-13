
#include <iomanip>
#include <memory>
#include <sstream>

#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"
#include "../../Utils/fraction.h"
#include "../../Utils/Numeric.h"

using namespace std;

NumExpression::NumExpression(double real, double imag): real{real}, imag{imag} {}
NumExpression::NumExpression(const std::string& num): real{0}, imag{0} {
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

expression NumExpression::simplify() {
    return copy();
}
expression NumExpression::derivative(const std::string& var) {
    return construct(0);
}
expression NumExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: NumExpression::integrate"));
}

bool NumExpression::evaluable() const { return !gsl_isnan(real) && !gsl_isnan(imag); }

expression NumExpression::evaluate(const Variables& vars) {
    if (evaluable()){ return copy(); }
    return InvalidExpression::construct(Exception("Invalid Number."));
}

double NumExpression::value(const Variables& vars) const { return real; }

gsl_complex NumExpression::complex() const { return gsl_complex{real, imag}; }
gsl_complex NumExpression::complex(const Variables& vars) const { return gsl_complex{real, imag}; }

bool NumExpression::isComplex() const { return imag != 0; }

bool NumExpression::isEqual(expression e, double precision) const {
    if (e->num()){
        return compare(complex(), e->complex(), precision) == 0;
    }
    return false;
}

std::ostream& NumExpression::print(std::ostream& out) const {
    if (!evaluable()){
        return out << "NaN";
    }
    if (real == 0 && imag == 0){
        return out << "0";
    }
    if (real != 0){
        out << std::setprecision(16) << real;
        if (imag > 0){ out << "+"; }
    }
    if (imag != 0){
        out << std::setprecision(16) << imag << "i";
    }
    return out;
}

std::ostream& NumExpression::postfix(std::ostream& out) const {
    if (!evaluable()){
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

bool NumExpression::prettyprint(std::ostream& out) const {
    if (!evaluable()){
        return false;
    }
    if (imag == 0){
        long numerator, denominator;
        if (to_fraction(real, numerator, denominator) && denominator != 1 &&
            std::abs(numerator) < 1e6 && std::abs(denominator) < 1e6){
            out << numerator << "/" << denominator;
            return true;
        }
    }
    return false;
}
