
#include <memory>
#include <ostream>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../ExpressionOperations.h"
#include "../NullExpression.h"

using namespace std;
using namespace Scanner;

EmptyExpression::EmptyExpression(): Expression{EMPTY} {}

expression EmptyExpression::construct() {
    return shared_ptr<EmptyExpression>(new EmptyExpression());
}

expression Empty = EmptyExpression::construct();

expression EmptyExpression::eval(const Variables& vars) { return copy(); }
double EmptyExpression::value(const Variables& vars) const { return GSL_NAN; }

bool EmptyExpression::isComplex() const { return false; }
bool EmptyExpression::isEvaluable(const Variables& vars) const { return false; }
bool EmptyExpression::equals(expression e, double precision) const { return e == EMPTY; }

std::ostream& EmptyExpression::print(std::ostream& out, const bool pretty) const {
    return out << "Empty";
}
std::ostream& EmptyExpression::postfix(std::ostream& out) const {
    return out << "Empty";
}
