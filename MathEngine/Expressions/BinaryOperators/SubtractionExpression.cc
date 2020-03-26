
#include "../BinaryOperators.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

SubtractionExpression::SubtractionExpression(expression lhs, expression rhs):
    lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression SubtractionExpression::simplify() {
    return lhs->simplify() - rhs->simplify();
}
expression SubtractionExpression::derivative(const std::string& var) {
    return lhs->derivative(var) - rhs->derivative(var);
}
expression SubtractionExpression::integrate(const std::string& var) {
    return lhs->integrate(var) - rhs->integrate(var);
}

double SubtractionExpression::value() { return lhs->value() - rhs->value(); }
double SubtractionExpression::value(const Variables& vars) { return lhs->value(vars) - rhs->value(vars); }

expression SubtractionExpression::copy() {
    return lhs->copy() - rhs->copy();
}

std::ostream& SubtractionExpression::print(std::ostream& out) {
    lhs->print(out);
    out << "-";
    return rhs->print(out);
}


expression operator-(expression&& expr1, expression&&expr2){
    return make_unique<SubtractionExpression>(std::move(expr1), std::move(expr2));
}
