
#include "../BinaryOperators.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

MultiplicationExpression::MultiplicationExpression(expression lhs, expression rhs):
    lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression MultiplicationExpression::simplify() {
    throw Exception("Unimplemented Error: MultiplicationExpression::simplify");
    // return make_unique<MultiplicationExpression>(
    //     lhs->simplify(),
    //     rhs->simplify()
    // );
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

double MultiplicationExpression::value() { return lhs->value() * rhs->value(); }
double MultiplicationExpression::value(const Variables& vars) { return lhs->value(vars) * rhs->value(vars); }

expression MultiplicationExpression::copy() {
    return lhs->copy() * rhs->copy();
}

std::ostream& MultiplicationExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "*";
    return rhs->print(out);
}


expression operator*(expression&& expr1, expression&&expr2){
    return make_unique<MultiplicationExpression>(std::move(expr1), std::move(expr2));
}

