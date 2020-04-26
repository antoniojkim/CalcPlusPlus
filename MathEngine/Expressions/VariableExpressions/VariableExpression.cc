
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../NumericalExpression.h"
#include "../UnitConversionExpression/Units.h"
#include "../UnitExpression.h"
#include "../VariableExpression.h"

using namespace std;

VariableExpression::VariableExpression(const std::string& name): name{name}, num{GSL_NAN} {}
VariableExpression::VariableExpression(const std::string& name, double num): name{name}, num{num} {}

expression VariableExpression::construct(const std::string& name){
    return unique_ptr<VariableExpression>(new VariableExpression(name));
}
expression VariableExpression::construct(const std::string& name, double num){
    return unique_ptr<VariableExpression>(new VariableExpression(name, num));
}

expression VariableExpression::simplify() {
    return copy();
}
expression VariableExpression::derivative(const std::string& var) {
    if (var == name){
        return NumExpression::construct(1);
    }
    return NumExpression::construct(0);
}
expression VariableExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: VariableExpression::integrate");
}

bool VariableExpression::evaluable(){ return !gsl_isnan(num); }

expression VariableExpression::evaluate(const Variables& vars){
    if (vars.count(name) == 0){
        if (getAbbrIndex(name) != -1 || getUnitIndex(name) != -1){
            return UnitExpression::construct(name);
        }
        return copy();
    }
    return vars.at(name)->evaluate();
}

double VariableExpression::value(const Variables& vars) {
    if (vars.count(name) > 0){
        return vars.at(name)->value();
    }
    return num;
}

bool VariableExpression::isComplex(){ return false; }

expression VariableExpression::copy() {
    return construct(name, num);
}

std::ostream& VariableExpression::print(std::ostream& out) {
    return out << name;
}
std::ostream& VariableExpression::postfix(std::ostream& out) {
    return out << name;
}
