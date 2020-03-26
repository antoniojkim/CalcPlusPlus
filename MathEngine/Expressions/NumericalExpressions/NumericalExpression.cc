
#include <sstream>

#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

expression Expression::evaluate(){ return std::make_unique<NumericalExpression>(this->value()); }

NumericalExpression::NumericalExpression(double real, double imag): real{real}, imag{imag} {}
NumericalExpression::NumericalExpression(const std::string& num): real{0}, imag{0} {
    istringstream iss{num};
    if (!(iss >> real)){
        throw Exception("Number Error: Invalid Number ", num);
    }
    char i;
    if ((iss >> i) && i == 'i'){
        imag = real;
        real = 0;
    }
}

expression NumericalExpression::simplify() {
    return make_unique<NumericalExpression>(real, imag);
}
expression NumericalExpression::derivative(const std::string& var) {
    return make_unique<NumericalExpression>(0);
}
expression NumericalExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: NumericalExpression::integrate");
}

bool NumericalExpression::evaluable(){ return true; }

double NumericalExpression::value() { return real; }

double NumericalExpression::value(const Variables& vars) { return real; }

bool NumericalExpression::complex(){ return imag != 0; }

expression NumericalExpression::copy() {
    return make_unique<NumericalExpression>(real, imag);
}

std::ostream& NumericalExpression::print(std::ostream& out) {
    out << real;
    if (imag > 0){
        out << '+' << imag << "i";
    }
    else if (imag < 0){
        out << imag << "i";
    }
    return out;
}
