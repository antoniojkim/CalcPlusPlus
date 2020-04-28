
#include <iomanip>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../NumericalExpression.h"
#include "../UnitConversionExpression/Units.h"
#include "../UnitExpression.h"
#include "../VariableExpression.h"
#include "Constants.h"

using namespace std;

VariableExpression::VariableExpression(const std::string& name): name{name}, num{GSL_NAN} {}
VariableExpression::VariableExpression(const std::string& name, double num): name{name}, num{num} {}

expression VariableExpression::construct(const std::string& name){
    return shared_ptr<VariableExpression>(new VariableExpression(name));
}
expression VariableExpression::construct(const std::string& name, double num){
    return shared_ptr<VariableExpression>(new VariableExpression(name, num));
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

bool VariableExpression::evaluable() const {
    return !gsl_isnan(num) || getConstantIndex(name) != -1;
}

expression VariableExpression::evaluate(const Variables& vars) {
    if (vars.count(name) == 0){
        if (getConstantIndex(name) != -1){
            return copy();
        }
        if (getAbbrIndex(name) != -1 || getUnitIndex(name) != -1){
            return BaseUnitExpression::construct(name);
        }
        return copy();
    }
    return vars.at(name)->evaluate();
}

double VariableExpression::value(const Variables& vars) const {
    if (vars.count(name) > 0){
        return vars.at(name)->value();
    }
    if (getConstantIndex(name) != -1){
        return getConstantValue(name);
    }
    return num;
}

bool VariableExpression::isComplex() const { return false; }

std::ostream& VariableExpression::print(std::ostream& out) const {
    if (gsl_isnan(num)){
        return out << name;
    }
    else if (getConstantIndex(name) != -1){
        return out << std::setprecision(16) << getConstantValue(name);
    }
    else{
        return out << std::setprecision(16) << num;
    }
}
std::ostream& VariableExpression::postfix(std::ostream& out) const {
    return out << name;
}
