
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

IntegerDivisionExpression::IntegerDivisionExpression(expression&& lhs, expression&&rhs):
    lhs{std::move(lhs)}, rhs{std:move(rhs)} {}

expression IntegerDivisionExpression::simplify() {
    return make_unique<IntegerDivisionExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression IntegerDivisionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: IntegerDivisionExpression::derivative");
    // return make_unique<IntegerDivisionExpression>(
    //     lhs->derivative(var),
    //     rhs->derivative(var)
    // );
}
expression IntegerDivisionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: IntegerDivisionExpression::integrate");
    // return make_unique<IntegerDivisionExpression>(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool IntegerDivisionExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }

double IntegerDivisionExpression::value() { return int(lhs->value() / rhs->value()); }
double IntegerDivisionExpression::value(const Variables& vars) { return int(lhs->value(vars) / rhs->value(vars)); }

bool IntegerDivisionExpression::complex(){ return lhs->complex() || rhs->complex(); }

expression IntegerDivisionExpression::copy() {
    return make_unique<IntegerDivisionExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

std::ostream& IntegerDivisionExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "//";
    return rhs->print(out);
}
