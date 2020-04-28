
#include <utility>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"
#include "BinaryOperatorDirectory.h"
#include "Operators.h"

using namespace std;

BinaryOperatorExpression::BinaryOperatorExpression(const char * lexeme, expression lhs, expression rhs):
    operatorIndex{getOperatorIndex(lexeme)}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
BinaryOperatorExpression::BinaryOperatorExpression(std::string& lexeme, expression lhs, expression rhs):
    operatorIndex{getOperatorIndex(lexeme)}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
BinaryOperatorExpression::BinaryOperatorExpression(int operatorIndex, expression lhs, expression rhs):
    operatorIndex{operatorIndex}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression BinaryOperatorExpression::construct(const char * lexeme, expression lhs, expression rhs){
    return shared_ptr<BinaryOperatorExpression>(new BinaryOperatorExpression(lexeme, std::move(lhs), std::move(rhs)));
}
expression BinaryOperatorExpression::construct(std::string& lexeme, expression lhs, expression rhs){
    return shared_ptr<BinaryOperatorExpression>(new BinaryOperatorExpression(lexeme, std::move(lhs), std::move(rhs)));
}
expression BinaryOperatorExpression::construct(int operatorIndex, expression lhs, expression rhs){
    return shared_ptr<BinaryOperatorExpression>(new BinaryOperatorExpression(operatorIndex, std::move(lhs), std::move(rhs)));
}

expression BinaryOperatorExpression::evaluate(const Variables& vars) {
    auto fe = getBinaryOperatorExpr(operatorIndex);
    if (fe){ return fe(lhs, rhs, vars); }
    return NumExpression::construct(value(vars));
}

expression BinaryOperatorExpression::simplify() {
    auto fsimplify = getBinaryOperatorSimplify(operatorIndex);
    if (fsimplify){ return fsimplify(lhs, rhs); }
    return this->copy();
}
expression BinaryOperatorExpression::derivative(const std::string& var) {
    auto fprime = getBinaryOperatorDerivative(operatorIndex);
    if (fprime){ return fprime(lhs, rhs, var); }
    return InvalidExpression::construct(Exception("Derivative not defined for: ", operators[operatorIndex]));
}
expression BinaryOperatorExpression::integrate(const std::string& var) {
    auto fint = getBinaryOperatorIntegral(operatorIndex);
    if (fint){ return fint(lhs, rhs, var); }
    return InvalidExpression::construct(Exception("Integrate not defined for: ", operators[operatorIndex]));
}

double BinaryOperatorExpression::value(const Variables& vars) const {
    auto f = getBinaryOperator(operatorIndex);
    if (f){ return f(lhs->value(vars), rhs->value(vars)); }
    return GSL_NAN;
}

bool BinaryOperatorExpression::evaluable() const { return lhs->evaluable() && rhs->evaluable(); }
bool BinaryOperatorExpression::isComplex() const { return lhs->isComplex() || rhs->isComplex(); }

std::ostream& BinaryOperatorExpression::print(std::ostream& out) const {
    if (lhs->binaryOperator() &&
        getPrecedence((Scanner::Type) lhs->binaryOperator()->operatorIndex) < getPrecedence((Scanner::Type) operatorIndex)){
        out << "("; lhs->print(out) << ")";
    }
    else{
        lhs->print(out);
    }
    out << " " << operators[operatorIndex] << " ";
    if (rhs->binaryOperator() &&
        getPrecedence((Scanner::Type) rhs->binaryOperator()->operatorIndex) < getPrecedence((Scanner::Type) operatorIndex)){
        out << "("; rhs->print(out) << ")";
    }
    else{
        rhs->print(out);
    }
    return out;
}
std::ostream& BinaryOperatorExpression::postfix(std::ostream& out) const {
    lhs->postfix(out) << ' ';
    return  rhs->postfix(out) << ' ' << operators[operatorIndex];
}
