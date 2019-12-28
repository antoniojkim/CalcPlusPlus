
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

SubtractionExpression::SubtractionExpression(expression&& lhs, expression&&rhs):
    lhs{std::move(lhs)}, rhs{std:move(rhs)} {}

expression SubtractionExpression::simplify() {
    return make_unique<SubtractionExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression SubtractionExpression::derivative(const std::string& var) {
    return make_unique<SubtractionExpression>(
        lhs->derivative(var),
        rhs->derivative(var)
    );
}
expression SubtractionExpression::integrate(const std::string& var) {
    return make_unique<SubtractionExpression>(
        lhs->integrate(var),
        rhs->integrate(var)
    );
}

bool SubtractionExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }

double SubtractionExpression::value() { return lhs->value() - rhs->value(); }
double SubtractionExpression::value(const double& x) { return lhs->value(x) - rhs->value(x); }
double SubtractionExpression::value(const double& x, const double& y) { return lhs->value(x, y) - rhs->value(x, y); }

bool SubtractionExpression::complex(){ return lhs->complex() || rhs->complex(); }

expression SubtractionExpression::copy() {
    return make_unique<SubtractionExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

std::ostream& SubtractionExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "-";
    return rhs->print(out);
}

