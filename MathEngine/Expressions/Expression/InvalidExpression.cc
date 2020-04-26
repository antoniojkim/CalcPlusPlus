
#include <memory>
#include <ostream>

#include <gsl/gsl_math.h>

#include "../InvalidExpression.h"

using namespace std;

InvalidExpression::InvalidExpression(const string& msg): message{msg} {}

expression InvalidExpression::construct(const string& msg) {
    return unique_ptr<InvalidExpression>(new InvalidExpression(msg));
}
expression InvalidExpression::construct(const Exception& e) {
    return unique_ptr<InvalidExpression>(new InvalidExpression(e.msg));
}


expression InvalidExpression::simplify() {
    return InvalidExpression::construct(message);
}
expression InvalidExpression::derivative(const std::string& var) {
    return InvalidExpression::construct(message);
}
expression InvalidExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(message);
}

bool InvalidExpression::evaluable(){ return false; }


double InvalidExpression::value(const Variables& vars) { return GSL_NAN; }

bool InvalidExpression::isComplex(){ return false; }

expression InvalidExpression::copy() {
    return InvalidExpression::construct(message);
}

std::ostream& InvalidExpression::print(std::ostream& out) {
    return out << message;
}

std::ostream& InvalidExpression::postfix(std::ostream& out) {
    return out << message;
}
