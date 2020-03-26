
#include "../BinaryOperators.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

AdditionExpression::AdditionExpression(expression lhs, expression rhs):
    lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression AdditionExpression::simplify() {
    return lhs->simplify() + rhs->simplify();
}
expression AdditionExpression::derivative(const std::string& var) {
    return lhs->derivative(var) + rhs->derivative(var);
}
expression AdditionExpression::integrate(const std::string& var) {
    return lhs->integrate(var) + rhs->integrate(var);
}

double AdditionExpression::value() { return lhs->value() + rhs->value(); }
double AdditionExpression::value(const Variables& vars) { return lhs->value(vars) + rhs->value(vars); }

expression AdditionExpression::copy() {
    return lhs->copy() + rhs->copy();
}

std::ostream& AdditionExpression::print(std::ostream& out) {
    lhs->print(out) << "+";
    return rhs->print(out);
}


expression operator+(expression&& expr1, expression&&expr2){
    return make_unique<AdditionExpression>(std::move(expr1), std::move(expr2));
}

