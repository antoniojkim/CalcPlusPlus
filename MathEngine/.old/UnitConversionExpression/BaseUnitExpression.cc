
#include <iomanip>
#include <memory>
#include <sstream>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../InvalidExpression.h"
#include "../UnitExpression.h"
#include "Units.h"

using namespace std;
using namespace Scanner;

BaseUnitExpression::BaseUnitExpression(const std::string& unit, double val): abbr{unit}, val{val} {
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
BaseUnitExpression::BaseUnitExpression(UnitType type, const std::string& unit, double val): type{type}, abbr{unit}, val{val} {}

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

bool BaseUnitExpression::compare(UnitType type, double val){
    return this->type == type && this->val == val;
}

bool BaseUnitExpression::equals(expression e, double precision) const {
    if (e == UNIT){
        return type == e->unit()->type && val == e->unit()->val;
    }
    return false;
}

std::ostream& BaseUnitExpression::print(std::ostream& out) const {
    return out << abbr;
}

std::ostream& BaseUnitExpression::postfix(std::ostream& out) const {
    return out << abbr;
}
