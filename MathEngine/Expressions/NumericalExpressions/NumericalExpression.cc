
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

expression Expression::evaluate(){ return std::make_unique<NumericalExpression>(this->value()); }

NumericalExpression::NumericalExpression(double num): num{num}{}

expression NumericalExpression::simplify() {
    return make_unique<NumericalExpression>(num);
}
expression NumericalExpression::derivative(const std::string& var) {
    return make_unique<NumericalExpression>(0);
}
expression NumericalExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: NumericalExpression::integrate");
}

bool NumericalExpression::evaluable(){ return true; }

double NumericalExpression::value() { return num; }

double NumericalExpression::value(const double& x) { return num; }
double NumericalExpression::value(const double& x, const double& y) { return num; }

bool NumericalExpression::complex(){ return false; }

expression NumericalExpression::copy() {
    return make_unique<NumericalExpression>(num);
}
