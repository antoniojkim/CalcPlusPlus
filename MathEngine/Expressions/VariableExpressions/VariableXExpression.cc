
#include "../NumericalExpression.h"
#include "../VariableExpression.h"
#include "../../Utils/exceptions.h"

#include <gsl/gsl_math.h>

using namespace std;

VariableXExpression::VariableXExpression(){}

expression VariableXExpression::simplify() {
    return copy();
}
expression VariableXExpression::derivative(const std::string& var) {
    if (var == "x"){
        return make_unique<NumericalExpression>(1); 
    }
    return make_unique<NumericalExpression>(0);
}
expression VariableXExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: VariableXExpression::integrate");
}

bool VariableXExpression::evaluable(){ return false; }

double VariableXExpression::value() { return GSL_NAN; }

double VariableXExpression::value(const double& x) { return x; }
double VariableXExpression::value(const double& x, const double& y) { return x; }

bool VariableXExpression::complex(){ return false; }

expression VariableXExpression::copy() {
    return make_unique<VariableXExpression>();
}

std::ostream& VariableXExpression::print(std::ostream& out) {
    return out << "x";
}
