
#include "../BinaryOperators.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

DivisionExpression::DivisionExpression(expression lhs, expression rhs):
    lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression DivisionExpression::simplify() {
    throw Exception("Unimplemented Error: DivisionExpression::simplify");
    // return make_unique<DivisionExpression>(
    //     lhs->simplify(),
    //     rhs->simplify()
    // );
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

double DivisionExpression::value() { return lhs->value() / rhs->value(); }
double DivisionExpression::value(const Variables& vars) { return lhs->value(vars) / rhs->value(vars); }

expression DivisionExpression::copy() {
    return lhs->copy() / rhs->copy();
}

std::ostream& DivisionExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "/";
    return rhs->print(out);
}

expression operator/(expression&& expr1, expression&&expr2){
    return make_unique<DivisionExpression>(std::move(expr1), std::move(expr2));
}
