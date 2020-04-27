
#include <iomanip>
#include <memory>
#include <sstream>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../UnitExpression.h"
#include "Units.h"

using namespace std;

ConvertedUnitExpression::ConvertedUnitExpression(UnitType type, const std::string& unit, double val): type{type}, abbr{unit}, val{val} {}

expression ConvertedUnitExpression::construct(UnitType type, const std::string& unit, double val){
    return unique_ptr<ConvertedUnitExpression>(new ConvertedUnitExpression(type, unit, val));
}

expression ConvertedUnitExpression::evaluate(const Variables& vars){
    return copy();
}

expression ConvertedUnitExpression::simplify() {
    return copy();
}
expression ConvertedUnitExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: ConvertedUnitExpression::derivative");
}
expression ConvertedUnitExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: ConvertedUnitExpression::integrate");
}

bool ConvertedUnitExpression::evaluable(){ return true; }

double ConvertedUnitExpression::value(const Variables& vars) { return val; }

bool ConvertedUnitExpression::isComplex(){ return false; }

expression ConvertedUnitExpression::copy() {
    return ConvertedUnitExpression::construct(type, abbr, val);
}

std::ostream& ConvertedUnitExpression::print(std::ostream& out) {
    return out << val << abbr;
}

std::ostream& ConvertedUnitExpression::postfix(std::ostream& out) {
    return out << val << abbr;
}
