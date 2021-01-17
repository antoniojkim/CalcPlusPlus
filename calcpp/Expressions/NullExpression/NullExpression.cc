
#include <memory>
#include <ostream>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../ExpressionOperations.h"
#include "../NullExpression.h"

using namespace std;
using namespace Scanner;

NullExpression::NullExpression(): Expression{NONE} {}

expression NullExpression::construct() {
    return shared_ptr<NullExpression>(new NullExpression());
}

expression None = NullExpression::construct();

expression NullExpression::eval(const Variables& vars) { return copy(); }
double NullExpression::value(const Variables& vars) const { return GSL_NAN; }

bool NullExpression::isComplex() const { return false; }
bool NullExpression::isEvaluable(const Variables& vars) const { return false; }
bool NullExpression::equals(expression e, double precision) const { return e == NONE; }

std::ostream& NullExpression::print(std::ostream& out, const bool pretty) const {
    return out << "None";
}
std::ostream& NullExpression::postfix(std::ostream& out) const {
    return out << "None";
}
