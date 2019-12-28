
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

DivisionExpression::DivisionExpression(expression&& lhs, expression&&rhs):
    lhs{std::move(lhs)}, rhs{std:move(rhs)} {}

expression DivisionExpression::simplify() {
    return make_unique<DivisionExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression DivisionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: DivisionExpression::derivative");
    // return make_unique<DivisionExpression>(
    //     lhs->derivative(var),
    //     rhs->derivative(var)
    // );
}
expression DivisionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: DivisionExpression::integrate");
    // return make_unique<DivisionExpression>(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool DivisionExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }

double DivisionExpression::value() { return lhs->value() / rhs->value(); }
double DivisionExpression::value(const double& x) { return lhs->value(x) / rhs->value(x); }
double DivisionExpression::value(const double& x, const double& y) { return lhs->value(x, y) / rhs->value(x, y); }

bool DivisionExpression::complex(){ return lhs->complex() || rhs->complex(); }

expression DivisionExpression::copy() {
    return make_unique<DivisionExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

std::ostream& DivisionExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "/";
    return rhs->print(out);
}
