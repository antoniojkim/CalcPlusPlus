
#include <memory>
#include <ostream>

#include <gsl/gsl_math.h>

#include "../InvalidExpression.h"

using namespace std;

InvalidExpression::InvalidExpression(const string& msg): message{msg} {}

expression InvalidExpression::construct(const string& msg) {
    return shared_ptr<InvalidExpression>(new InvalidExpression(msg));
}
expression InvalidExpression::construct(const Exception& e) {
    return shared_ptr<InvalidExpression>(new InvalidExpression(e.msg));
}


expression InvalidExpression::simplify() { return copy(); }
expression InvalidExpression::derivative(const std::string& var) { return copy(); }
expression InvalidExpression::integrate(const std::string& var) { return copy(); }

bool InvalidExpression::evaluable() const { return false; }

expression InvalidExpression::evaluate(const Variables& vars) { return copy(); }

double InvalidExpression::value(const Variables& vars) const { return GSL_NAN; }

bool InvalidExpression::isComplex() const { return false; }

std::ostream& InvalidExpression::print(std::ostream& out) const {
    return out << message;
}

std::ostream& InvalidExpression::postfix(std::ostream& out) const {
    return out << message;
}
