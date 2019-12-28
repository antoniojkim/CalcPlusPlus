
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <cmath>
#include <utility>

using namespace std;

ExponentExpression::ExponentExpression(expression&& lhs, expression&&rhs):
    lhs{std::move(lhs)}, rhs{std:move(rhs)} {}

expression ExponentExpression::simplify() {
    return make_unique<ExponentExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression ExponentExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: ExponentExpression::derivative");
    // return make_unique<ExponentExpression>(
    //     lhs->derivative(var),
    //     rhs->derivative(var)
    // );
}
expression ExponentExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: ExponentExpression::integrate");
    // return make_unique<ExponentExpression>(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool ExponentExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }

double ExponentExpression::value() { return pow(lhs->value(), rhs->value()); }
double ExponentExpression::value(const double& x) { return pow(lhs->value(x), rhs->value(x)); }
double ExponentExpression::value(const double& x, const double& y) { return pow(lhs->value(x, y), rhs->value(x, y)); }

bool ExponentExpression::complex(){ return lhs->complex() || rhs->complex(); }

expression ExponentExpression::copy() {
    return make_unique<ExponentExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

std::ostream& ExponentExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "^";
    return rhs->print(out);
}

