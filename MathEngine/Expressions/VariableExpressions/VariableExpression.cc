
#include <iomanip>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"
#include "../UnitConversionExpression/Units.h"
#include "../UnitExpression.h"
#include "../VariableExpression.h"
#include "Constants.h"

using namespace std;
using namespace Scanner;

VariableExpression::VariableExpression(const std::string& name, expression var): Expression{VAR}, name{name}, var{var} {}

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


bool VariableExpression::isComplex() const {
    if (var){
        return var->isComplex();
    }
    return false;
}
bool VariableExpression::isEvaluable(const Variables& vars) const {
    return vars.count(name) != 0 || (var && var->isEvaluable(vars)) || getConstantIndex(name) != -1;
}

expression VariableExpression::eval(const Variables& vars) {
    if (var){
        return var->eval(vars);
    }
    if (vars.count(name) == 0){
        if (getConstantIndex(name) != -1){
            return copy();
        }
        if (getAbbrIndex(name) != -1 || getUnitIndex(name) != -1){
            return BaseUnitExpression::construct(name);
        }
        return copy();
    }
    return vars.at(name);  // ->eval(vars);
}

double VariableExpression::value(const Variables& vars) const {
    if (var){
        return var->value(vars);
    }
    if (vars.count(name) > 0){
        return vars.at(name)->value();
    }
    if (getConstantIndex(name) != -1){
        return getConstantValue(name);
    }
    return GSL_NAN;
}


bool VariableExpression::equals(expression e, double precision) const {
    if (e == VAR){
        return name == e->repr() && ((!var && !e->at(0)) || (var && e->at(0) && var->equals(e->at(0), precision)));
    }
    return false;
}

expression VariableExpression::at(const int index) {
    if (index == 0){
        return var;
    }
    return nullptr;
}

std::ostream& VariableExpression::print(std::ostream& out, const bool pretty) const {
    if (!var){
        return out << name;
    }
    else if (getConstantIndex(name) != -1){
        return out << std::setprecision(16) << getConstantValue(name);
    }
    else{
        out << name << " = ";
        return var->print(out, pretty);
    }
}
std::ostream& VariableExpression::postfix(std::ostream& out) const {
    return out << name;
}
