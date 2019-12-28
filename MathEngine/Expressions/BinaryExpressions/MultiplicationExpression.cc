
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

MultiplicationExpression::MultiplicationExpression(expression&& lhs, expression&&rhs):
    lhs{std::move(lhs)}, rhs{std:move(rhs)} {}

expression MultiplicationExpression::simplify() {
    return make_unique<MultiplicationExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression MultiplicationExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: MultiplicationExpression::derivative");
    // return make_unique<MultiplicationExpression>(
    //     lhs->derivative(var),
    //     rhs->derivative(var)
    // );
}
expression MultiplicationExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: MultiplicationExpression::integrate");
    // return make_unique<MultiplicationExpression>(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool MultiplicationExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }

double MultiplicationExpression::value() { return lhs->value() * rhs->value(); }
double MultiplicationExpression::value(const double& x) { return lhs->value(x) * rhs->value(x); }
double MultiplicationExpression::value(const double& x, const double& y) { return lhs->value(x, y) * rhs->value(x, y); }

bool MultiplicationExpression::complex(){ return lhs->complex() || rhs->complex(); }

expression MultiplicationExpression::copy() {
    return make_unique<MultiplicationExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

std::ostream& MultiplicationExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "*";
    return rhs->print(out);
}

