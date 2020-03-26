
#include "../BinaryOperators.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <cmath>
#include <utility>

using namespace std;

ModulusDivisionExpression::ModulusDivisionExpression(expression lhs, expression rhs):
    lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression ModulusDivisionExpression::simplify() {
    return make_unique<ModulusDivisionExpression>(
        lhs->simplify(),
        rhs->simplify()
    );
}
expression ModulusDivisionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: ModulusDivisionExpression::derivative");
    // return make_unique<ModulusDivisionExpression>(
    //     lhs->derivative(var),
    //     rhs->derivative(var)
    // );
}
expression ModulusDivisionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: ModulusDivisionExpression::integrate");
    // return make_unique<ModulusDivisionExpression>(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

double ModulusDivisionExpression::value() { return fmod(lhs->value(), rhs->value()); }
double ModulusDivisionExpression::value(const Variables& vars) { return fmod(lhs->value(vars), rhs->value(vars)); }

expression ModulusDivisionExpression::copy() {
    return make_unique<ModulusDivisionExpression>(
        lhs->copy(),
        rhs->copy()
    );
}

std::ostream& ModulusDivisionExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "%";
    return rhs->print(out);
}
