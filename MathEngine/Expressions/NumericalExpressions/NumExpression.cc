
#include <iomanip>
#include <sstream>

#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

NumExpression::NumExpression(double real, double imag): real{real}, imag{imag} {}
NumExpression::NumExpression(const gsl_complex& z): real{GSL_REAL(z)}, imag{GSL_IMAG(z)} {}
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

expression NumExpression::simplify() {
    return make_unique<NumExpression>(real, imag);
}
expression NumExpression::derivative(const std::string& var) {
    return make_unique<NumExpression>(0);
}
expression NumExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: NumExpression::integrate");
}

bool NumExpression::evaluable(){ return true; }

double NumExpression::value(const Variables& vars) { return real; }

gsl_complex NumExpression::complex() { return gsl_complex{real, imag}; }
gsl_complex NumExpression::complex(const Variables& vars) { return gsl_complex{real, imag}; }

bool NumExpression::isComplex(){ return imag != 0; }

expression NumExpression::copy() {
    return make_unique<NumExpression>(real, imag);
}

std::ostream& NumExpression::print(std::ostream& out) {
    if (real != 0){
        out << std::setprecision(16) << real;
        if (imag > 0){ out << "+"; }
    }
    if (imag != 0){
        out << std::setprecision(16) << imag << "i";
    }
    return out;
}

std::ostream& NumExpression::postfix(std::ostream& out) {
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
