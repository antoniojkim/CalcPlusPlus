
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

ConvertedUnitExpression::ConvertedUnitExpression(UnitType type, const std::string& unit, double val):
    Expression(UNIT), type{type}, abbr{unit}, val{val} {}

expression ConvertedUnitExpression::construct(UnitType type, const std::string& unit, double val){
    return shared_ptr<ConvertedUnitExpression>(new ConvertedUnitExpression(type, unit, val));
}


expression ConvertedUnitExpression::eval(const Variables& vars) { return copy(); }

bool ConvertedUnitExpression::isComplex() const { return false; }
bool ConvertedUnitExpression::isEvaluable(const Variables& vars) const { return true; }

double ConvertedUnitExpression::value(const Variables& vars) const { return val; }


bool ConvertedUnitExpression::equals(expression e, double precision) const {
    if (e == UNIT){
        return type == e->id() && val == e->value();
    }
    return false;
}

std::string ConvertedUnitExpression::repr() const {
    return abbr;
}
int ConvertedUnitExpression::id() const {
    return (int) type;
}

std::ostream& ConvertedUnitExpression::print(std::ostream& out, const bool pretty) const {
    return out << val << abbr;
}

std::ostream& ConvertedUnitExpression::postfix(std::ostream& out) const {
    return out << val << abbr;
}
