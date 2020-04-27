
#include <iomanip>
#include <memory>
#include <sstream>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../UnitExpression.h"
#include "Units.h"

using namespace std;

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
    return unique_ptr<BaseUnitExpression>(new BaseUnitExpression(unit, val));
}
expression BaseUnitExpression::construct(UnitType type, const std::string& unit, double val){
    return unique_ptr<BaseUnitExpression>(new BaseUnitExpression(type, unit, val));
}

expression BaseUnitExpression::evaluate(const Variables& vars){
    return InvalidExpression::construct(Exception("Cannot evaluate a base unit expression."));
}

expression BaseUnitExpression::simplify() {
    return copy();
}
expression BaseUnitExpression::derivative(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: BaseUnitExpression::derivative"));
}
expression BaseUnitExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: BaseUnitExpression::integrate"));
}

bool BaseUnitExpression::evaluable(){ return false; }

double BaseUnitExpression::value(const Variables& vars) { return val; }

bool BaseUnitExpression::isComplex(){ return false; }

expression BaseUnitExpression::copy() {
    return BaseUnitExpression::construct(type, abbr, val);
}

std::ostream& BaseUnitExpression::print(std::ostream& out) {
    return out << abbr;
}

std::ostream& BaseUnitExpression::postfix(std::ostream& out) {
    return out << abbr;
}
