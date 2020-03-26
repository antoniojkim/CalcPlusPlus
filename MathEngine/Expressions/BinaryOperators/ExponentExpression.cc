
#include "../BinaryOperators.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <cmath>
#include <utility>

using namespace std;

ExponentExpression::ExponentExpression(expression lhs, expression rhs):
    lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression ExponentExpression::simplify() {
    throw Exception("Unimplemented Error: ExponentExpression::simplify");
    // return make_unique<ExponentExpression>(
    //     lhs->simplify(),
    //     rhs->simplify()
    // );
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

double ExponentExpression::value() { return pow(lhs->value(), rhs->value()); }
double ExponentExpression::value(const Variables& vars) { return pow(lhs->value(vars), rhs->value(vars)); }

expression ExponentExpression::copy() {
    return lhs->copy() ^ rhs->copy();
}

std::ostream& ExponentExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "^";
    return rhs->print(out);
}

expression operator^(expression&& expr1, expression&&expr2){
    return make_unique<ExponentExpression>(std::move(expr1), std::move(expr2));
}

