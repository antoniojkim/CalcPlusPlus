
#include "../NumericalExpression.h"
#include "../VariableExpression.h"
#include "../../Utils/exceptions.h"

#include <gsl/gsl_math.h>

using namespace std;

VariableYExpression::VariableYExpression(){}

expression VariableYExpression::simplify() {
    return copy();
}
expression VariableYExpression::derivative(const std::string& var) {
    if (var == "y"){
        return make_unique<NumericalExpression>(1);
    }
    return make_unique<NumericalExpression>(0);
}
expression VariableYExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: VariableYExpression::integrate");
}

bool VariableYExpression::evaluable(){ return false; }

double VariableYExpression::value() { return GSL_NAN; }

double VariableYExpression::value(const double& x) { return GSL_NAN; }
double VariableYExpression::value(const double& x, const double& y) { return y; }

bool VariableYExpression::complex(){ return false; }

expression VariableYExpression::copy() {
    return make_unique<VariableYExpression>();
}

std::ostream& VariableYExpression::print(std::ostream& out) {
    return out << "y";
}
