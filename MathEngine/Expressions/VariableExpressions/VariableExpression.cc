
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

VariableExpression::VariableExpression(const std::string& name, expression var): name{name}, var{var} {}

expression VariableExpression::construct(const std::string& name){
    return shared_ptr<VariableExpression>(new VariableExpression(name));
}
expression VariableExpression::construct(const std::string& name, double num){
    return shared_ptr<VariableExpression>(new VariableExpression(name, NumExpression::construct(num)));
}
expression VariableExpression::construct(const std::string& name, expression var){
    return shared_ptr<VariableExpression>(new VariableExpression(name, var));
}

expression VariableExpression::simplify() {
    if (var){
        return VariableExpression::construct(name, var->simplify());
    }
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
    return (var && var->evaluable()) || getConstantIndex(name) != -1;
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
    return vars.at(name)->evaluate(vars);
}

double VariableExpression::value(const Variables& vars) const {
    if (vars.count(name) > 0){
        return vars.at(name)->value();
    }
    if (getConstantIndex(name) != -1){
        return getConstantValue(name);
    }
    return var->value(vars);
}

bool VariableExpression::isComplex() const { return false; }

bool VariableExpression::isEqual(expression e, double precision) const {
    if (e->variable()){
        return name == e->variable()->name && var->isEqual(e->variable()->var);
    }
    return false;
}

std::ostream& VariableExpression::print(std::ostream& out) const {
    if (!var){
        return out << name;
    }
    else if (getConstantIndex(name) != -1){
        return out << std::setprecision(16) << getConstantValue(name);
    }
    else{
        return out << name << " = " << var;
    }
}
std::ostream& VariableExpression::postfix(std::ostream& out) const {
    return out << name;
}
