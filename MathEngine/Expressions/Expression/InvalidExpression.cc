
#include <memory>
#include <ostream>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../InvalidExpression.h"

using namespace std;
using namespace Scanner;

InvalidExpression::InvalidExpression(const string& msg): Expression{INVALID}, message{msg} {}

expression InvalidExpression::construct(const Exception& e) {
    return shared_ptr<InvalidExpression>(new InvalidExpression(e.msg));
}

expression InvalidExpression::eval(const Variables& vars) override { return copy(); }
double InvalidExpression::value(const Variables& vars) const { return GSL_NAN; }

bool InvalidExpression::isComplex() const { return false; }
bool InvalidExpression::isEvaluable() const { return false; }
bool InvalidExpression::equals(expression e, double precision) const { return false; }

std::ostream& InvalidExpression::print(std::ostream& out, const bool pretty) const {
    return out << message;
}
std::ostream& InvalidExpression::postfix(std::ostream& out) const {
    return out << message;
}
