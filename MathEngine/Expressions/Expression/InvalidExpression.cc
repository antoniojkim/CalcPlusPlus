
#include <sstream>
#include <gsl/gsl_math.h>

#include "../InvalidExpression.h"

using namespace std;

InvalidExpression::InvalidExpression(const Exception& e): message{e.msg} {}

expression InvalidExpression::simplify() {
    return make_unique<InvalidExpression>(message);
}
expression InvalidExpression::derivative(const std::string& var) {
    return make_unique<InvalidExpression>(message);
}
expression InvalidExpression::integrate(const std::string& var) {
    return make_unique<InvalidExpression>(message);
}

bool InvalidExpression::evaluable(){ return false; }


double InvalidExpression::value(const Variables& vars) { return GSL_NAN; }

bool InvalidExpression::isComplex(){ return false; }

expression InvalidExpression::copy() {
    return make_unique<InvalidExpression>(message);
}

std::ostream& InvalidExpression::print(std::ostream& out) {
    return out << message;
}

std::ostream& InvalidExpression::postfix(std::ostream& out) {
    return out << message;
}
