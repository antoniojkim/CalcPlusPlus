
#include <cmath>
#include <iomanip>
#include <sstream>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../UnitExpression.h"
#include "Units.h"

using namespace std;

UnitExpression::UnitExpression(const std::string& unit, double val): abbr{unit}, val{val} {
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
UnitExpression::UnitExpression(UnitType type, const std::string& unit, double val): type{type}, abbr{unit}, val{val} {}

expression UnitExpression::evaluate(const Variables& vars){
    return copy();
}

expression UnitExpression::simplify() {
    return copy();
}
expression UnitExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: UnitExpression::derivative");
}
expression UnitExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: UnitExpression::integrate");
}

bool UnitExpression::evaluable(){ return true; }

double UnitExpression::value(const Variables& vars) { return val; }

bool UnitExpression::isComplex(){ return false; }

expression UnitExpression::copy() {
    return make_unique<UnitExpression>(type, abbr, val);
}

std::ostream& UnitExpression::print(std::ostream& out) {
    return out << val << abbr;
}

std::ostream& UnitExpression::postfix(std::ostream& out) {
    return out << val << abbr;
}
