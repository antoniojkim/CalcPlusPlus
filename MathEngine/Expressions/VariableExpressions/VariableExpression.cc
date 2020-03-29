
#include <gsl/gsl_math.h>

#include "../NumericalExpression.h"
#include "../VariableExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

VariableExpression::VariableExpression(const std::string& name): name{name}, num{GSL_NAN} {}
VariableExpression::VariableExpression(const std::string& name, double num): name{name}, num{num} {}

expression VariableExpression::simplify() {
    return copy();
}
expression VariableExpression::derivative(const std::string& var) {
    if (var == name){
        return make_unique<NumExpression>(1);
    }
    return make_unique<NumExpression>(0);
}
expression VariableExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: VariableExpression::integrate");
}

bool VariableExpression::evaluable(){ return !gsl_isnan(num); }

double VariableExpression::value() { return num; }

double VariableExpression::value(const Variables& vars) {
    if (vars.count(name) > 0){
        return vars.at(name);
    }
    return num;
}

bool VariableExpression::complex(){ return false; }

expression VariableExpression::copy() {
    return make_unique<VariableExpression>(name, num);
}

std::ostream& VariableExpression::print(std::ostream& out) {
    return out << name;
}
std::ostream& VariableExpression::postfix(std::ostream& out) {
    return out << name;
}
