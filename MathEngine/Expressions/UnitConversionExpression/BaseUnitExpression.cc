
#include <iomanip>
#include <memory>
#include <sstream>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../InvalidExpression.h"
#include "../UnitExpression.h"
#include "Units.h"

using namespace std;
using namespace Scanner;

BaseUnitExpression::BaseUnitExpression(const std::string& unit, double val):
    Expression(UNIT), abbr{unit}, val{val} {
    int unitIndex = getAbbrIndex(unit);
    if (unitIndex == -1){
        unitIndex = getUnitIndex(unit);
        if (unitIndex == -1){
            throw Exception("Invalid Unit: ", unit);
        }
    }
    this->val *= getUnitConversion(unitIndex);
    type = getUnitType(unitIndex);
}
BaseUnitExpression::BaseUnitExpression(UnitType type, const std::string& unit, double val):
    Expression(UNIT), type{type}, abbr{unit}, val{val} {}

expression BaseUnitExpression::construct(const std::string& unit, double val){
    return shared_ptr<BaseUnitExpression>(new BaseUnitExpression(unit, val));
}
expression BaseUnitExpression::construct(UnitType type, const std::string& unit, double val){
    return shared_ptr<BaseUnitExpression>(new BaseUnitExpression(type, unit, val));
}


bool BaseUnitExpression::isComplex() const { return false; }
bool BaseUnitExpression::isEvaluable(const Variables& vars) const { return false; }

expression BaseUnitExpression::eval(const Variables& vars) {
    return copy();
}
double BaseUnitExpression::value(const Variables& vars) const { return val; }

bool BaseUnitExpression::equals(expression e, double precision) const {
    if (e == UNIT){
        return type == e->id() && val == e->value();
    }
    return false;
}

std::string BaseUnitExpression::repr() const {
    return abbr;
}
int BaseUnitExpression::id() const {
    return (int) type;
}

std::ostream& BaseUnitExpression::print(std::ostream& out, const bool pretty) const {
    return out << val << abbr;
}

std::ostream& BaseUnitExpression::postfix(std::ostream& out) const {
    return out << val << abbr;
}
