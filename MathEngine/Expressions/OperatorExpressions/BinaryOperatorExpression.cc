
#include "../../Utils/exceptions.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"
#include "BinaryOperatorDirectory.h"
#include "Operators.h"

#include <utility>

using namespace std;

BinaryOperatorExpression::BinaryOperatorExpression(const std::string& lexeme, expression&& lhs, expression&& rhs):
    BinaryOperatorExpression{getOperatorIndex(lexeme), std::move(lhs), std::move(rhs)} {}
BinaryOperatorExpression::BinaryOperatorExpression(int operatorIndex, expression&& lhs, expression&& rhs):
    operatorIndex{operatorIndex}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {
    f = getBinaryOperator(operatorIndex);
}

expression BinaryOperatorExpression::simplify() {
    if (fsimplify){
        return fsimplify(lhs, rhs);
    }
    return this->copy();
}
expression BinaryOperatorExpression::derivative(const std::string& var) {
    if (fprime){
        return fprime(lhs, rhs, var);
    }
    throw Exception("Derivative not defined for: ", operators[operatorIndex]);
}
expression BinaryOperatorExpression::integrate(const std::string& var) {
    if (fprime){
        return fint(lhs, rhs, var);
    }
    throw Exception("Integrate not defined for: ", operators[operatorIndex]);
}

double BinaryOperatorExpression::value(const Variables& vars) { return f(lhs->value(vars), rhs->value(vars)); }

expression BinaryOperatorExpression::copy() {
    return make_unique<BinaryOperatorExpression>(operatorIndex, lhs->copy(), rhs->copy());
}

bool BinaryOperatorExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }
bool BinaryOperatorExpression::isComplex(){ return lhs->isComplex() || rhs->isComplex(); }

std::ostream& BinaryOperatorExpression::print(std::ostream& out) {
    lhs->print(out) << operators[operatorIndex];
    return rhs->print(out);
}
std::ostream& BinaryOperatorExpression::postfix(std::ostream& out) {
    rhs->postfix(out) << ' ';
    return  lhs->postfix(out) << ' ' << operators[operatorIndex];
}


expression operator+(expression&& expr1, expression&&expr2) {
    int operatorIndex = getOperatorIndex("+");
    return make_unique<BinaryOperatorExpression>(operatorIndex, std::move(expr1), std::move(expr2));
}
expression operator-(expression&& expr1, expression&&expr2) {
    int operatorIndex = getOperatorIndex("-");
    return make_unique<BinaryOperatorExpression>(operatorIndex, std::move(expr1), std::move(expr2));
}
expression operator*(expression&& expr1, expression&&expr2) {
    int operatorIndex = getOperatorIndex("-");
    return make_unique<BinaryOperatorExpression>(operatorIndex, std::move(expr1), std::move(expr2));
}
expression operator/(expression&& expr1, expression&&expr2) {
    int operatorIndex = getOperatorIndex("/");
    return make_unique<BinaryOperatorExpression>(operatorIndex, std::move(expr1), std::move(expr2));
}
expression operator^(expression&& expr1, expression&&expr2) {
    int operatorIndex = getOperatorIndex("^");
    return make_unique<BinaryOperatorExpression>(operatorIndex, std::move(expr1), std::move(expr2));
}
