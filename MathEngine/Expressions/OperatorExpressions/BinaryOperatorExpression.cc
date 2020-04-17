
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"
#include "BinaryOperatorDirectory.h"
#include "Operators.h"

using namespace std;

BinaryOperatorExpression::BinaryOperatorExpression(const std::string& lexeme, expression&& lhs, expression&& rhs):
    operatorIndex{getOperatorIndex(lexeme)}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
BinaryOperatorExpression::BinaryOperatorExpression(int operatorIndex, expression&& lhs, expression&& rhs):
    operatorIndex{operatorIndex}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression BinaryOperatorExpression::evaluate(const Variables& vars){
    auto fe = getBinaryOperatorExpr(operatorIndex);
    if (fe){
        return fe(lhs, rhs, vars);
    }
    return make_unique<NumExpression>(value(vars));
}

expression BinaryOperatorExpression::simplify() {
    auto fsimplify = getBinaryOperatorSimplify(operatorIndex);
    if (fsimplify){
        return fsimplify(lhs, rhs);
    }
    return this->copy();
}
expression BinaryOperatorExpression::derivative(const std::string& var) {
    auto fprime = getBinaryOperatorDerivative(operatorIndex);
    if (fprime){
        return fprime(lhs, rhs, var);
    }
    return make_unique<InvalidExpression>(Exception("Derivative not defined for: ", operators[operatorIndex]));
}
expression BinaryOperatorExpression::integrate(const std::string& var) {
    auto fint = getBinaryOperatorIntegral(operatorIndex);
    if (fint){
        return fint(lhs, rhs, var);
    }
    return make_unique<InvalidExpression>(Exception("Integrate not defined for: ", operators[operatorIndex]));
}

double BinaryOperatorExpression::value(const Variables& vars) {
    auto f = getBinaryOperator(operatorIndex);
    if (f){
        return f(lhs->value(vars), rhs->value(vars));
    }
    return GSL_NAN;
}

expression BinaryOperatorExpression::copy() {
    return make_unique<BinaryOperatorExpression>(operatorIndex, lhs->copy(), rhs->copy());
}

bool BinaryOperatorExpression::evaluable(){ return lhs->evaluable() && rhs->evaluable(); }
bool BinaryOperatorExpression::isComplex(){ return lhs->isComplex() || rhs->isComplex(); }

std::ostream& BinaryOperatorExpression::print(std::ostream& out) {
    out << "(";
    lhs->print(out) << ") " << operators[operatorIndex] << " (";
    return rhs->print(out) << ")";
}
std::ostream& BinaryOperatorExpression::postfix(std::ostream& out) {
    lhs->postfix(out) << ' ';
    return  rhs->postfix(out) << ' ' << operators[operatorIndex];
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
