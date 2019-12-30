
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

double VariableXExpression::value(const Variables& vars) {
    if (vars.count("x") > 0){
        return vars.at("x");
    }
    return GSL_NAN;
}

bool VariableXExpression::complex(){ return false; }

expression VariableXExpression::copy() {
    return make_unique<VariableXExpression>();
}

std::ostream& VariableXExpression::print(std::ostream& out) {
    return out << "x";
}
