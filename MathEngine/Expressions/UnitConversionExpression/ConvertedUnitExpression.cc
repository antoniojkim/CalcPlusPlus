
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
    return shared_ptr<ConvertedUnitExpression>(new ConvertedUnitExpression(type, unit, val));
}

expression ConvertedUnitExpression::evaluate(const Variables& vars) {
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

bool ConvertedUnitExpression::evaluable() const { return true; }

double ConvertedUnitExpression::value(const Variables& vars) const { return val; }

bool ConvertedUnitExpression::isComplex() const { return false; }

bool ConvertedUnitExpression::isEqual(expression e, double precision) const {
    // if (e->variable()){
    //     return name == e->variable()->name && num == e->variable()->num;
    // }
    return false;
}

std::ostream& ConvertedUnitExpression::print(std::ostream& out) const {
    return out << val << abbr;
}

std::ostream& ConvertedUnitExpression::postfix(std::ostream& out) const {
    return out << val << abbr;
}
