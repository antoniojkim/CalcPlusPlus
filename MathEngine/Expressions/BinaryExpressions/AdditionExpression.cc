
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

AdditionExpression::AdditionExpression(expression&& lhs, expression&&rhs):
    lhs{std::move(lhs)}, rhs{std:move(rhs)} {}

expression AdditionExpression::simplify() {
    return make_unique<AdditionExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression AdditionExpression::derivative(const std::string& var) {
    return make_unique<AdditionExpression>(
        lhs->derivative(var),
        rhs->derivative(var)
    );
}
expression AdditionExpression::integrate(const std::string& var) {
    return make_unique<AdditionExpression>(
        lhs->integrate(var),
        rhs->integrate(var)
    );
}

bool AdditionExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }

double AdditionExpression::value() { return lhs->value() + rhs->value(); }
double AdditionExpression::value(const double& x) { return lhs->value(x) + rhs->value(x); }
double AdditionExpression::value(const double& x, const double& y) { return lhs->value(x, y) + rhs->value(x, y); }

bool AdditionExpression::complex(){ return lhs->complex() || rhs->complex(); }

expression AdditionExpression::copy() {
    return make_unique<AdditionExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

