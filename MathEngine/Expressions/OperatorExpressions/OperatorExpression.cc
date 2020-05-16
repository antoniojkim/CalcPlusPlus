
#include <utility>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../OperatorExpression.h"
#include "OperatorDirectory.h"
#include "Operators.h"

using namespace std;

OperatorExpression::OperatorExpression(int operatorIndex, expression lhs, expression rhs):
    operatorIndex{operatorIndex}, lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

expression OperatorExpression::construct(const char * lexeme, expression lhs, expression rhs){
    return shared_ptr<OperatorExpression>(new OperatorExpression(getOperatorIndex(lexeme), lhs, rhs));
}
expression OperatorExpression::construct(std::string& lexeme, expression lhs, expression rhs){
    return shared_ptr<OperatorExpression>(new OperatorExpression(getOperatorIndex(lexeme), lhs, rhs));
}
expression OperatorExpression::construct(int operatorIndex, expression lhs, expression rhs){
    return shared_ptr<OperatorExpression>(new OperatorExpression(operatorIndex, lhs, rhs));
}

expression OperatorExpression::evaluate(const Variables& vars) {
    auto fe = getOperatorExpr(operatorIndex);
    if (fe){ return fe(lhs, rhs, vars); }
    return NumExpression::construct(value(vars));
}

expression OperatorExpression::simplify() {
    if (lhs->evaluable() && rhs->evaluable()){
        return Expression::evaluate();
    }
    auto fsimplify = getOperatorSimplify(operatorIndex);
    if (fsimplify){ return fsimplify(lhs, rhs); }
    return this->copy();
}
expression OperatorExpression::derivative(const std::string& var) {
    auto fprime = getOperatorDerivative(operatorIndex);
    if (fprime){ return fprime(lhs, rhs, var); }
    return InvalidExpression::construct(Exception("Derivative not defined for: ", operators[operatorIndex]));
}
expression OperatorExpression::integrate(const std::string& var) {
    auto fint = getOperatorIntegral(operatorIndex);
    if (fint){ return fint(lhs, rhs, var); }
    return InvalidExpression::construct(Exception("Integrate not defined for: ", operators[operatorIndex]));
}

double OperatorExpression::value(const Variables& vars) const {
    if (isSingleOperator((Scanner::Type) operatorIndex)){
        auto f = getUnaryOperator(operatorIndex);
        if (f){ return f(lhs->value(vars)); }
    }
    else{
        auto f = getBinaryOperator(operatorIndex);
        if (f){ return f(lhs->value(vars), rhs->value(vars)); }
    }
    return GSL_NAN;
}

bool OperatorExpression::evaluable() const { return lhs->evaluable() && rhs->evaluable(); }
bool OperatorExpression::isComplex() const { return lhs->isComplex() || rhs->isComplex(); }

std::ostream& OperatorExpression::print(std::ostream& out) const {
    if (isSingleOperator((Scanner::Type) operatorIndex)){
        if (!isRightAssociative((Scanner::Type) operatorIndex)){
            out << operators[operatorIndex] << " ";
        }
        lhs->print(out);
        if (isRightAssociative((Scanner::Type) operatorIndex)){
            out << " " << operators[operatorIndex];
        }
    }
    else{
        if (lhs->operatorExpr() &&
            getPrecedence((Scanner::Type) lhs->operatorExpr()->operatorIndex) < getPrecedence((Scanner::Type) operatorIndex)){
            out << "("; lhs->print(out) << ")";
        }
        else{
            lhs->print(out);
        }
        out << " " << operators[operatorIndex] << " ";
        if (rhs->operatorExpr() &&
            getPrecedence((Scanner::Type) rhs->operatorExpr()->operatorIndex) < getPrecedence((Scanner::Type) operatorIndex)){
            out << "("; rhs->print(out) << ")";
        }
        else{
            rhs->print(out);
        }
    }
    return out;
}
std::ostream& OperatorExpression::postfix(std::ostream& out) const {
    lhs->postfix(out) << ' ';
    if (!isSingleOperator((Scanner::Type) operatorIndex)){
        rhs->postfix(out) << ' ';
    }
    return out << operators[operatorIndex];
}


expression pivot(OperatorExpression* o1, OperatorExpression* o2){
    if (o1->rhs != nullptr){
        return InvalidExpression::construct(Exception("Pivot expected e1 to have null rhs"));
    }
    int p1 = getPrecedence((Scanner::Type) o1->operatorIndex);
    int p2 = getPrecedence((Scanner::Type) o2->operatorIndex);
    if ((p1 > p2) || (p1 == p2 && !isRightAssociative((Scanner::Type) o2->operatorIndex))){
        o1->rhs = o2->lhs;
        o2->lhs = o1->copy();
        return o2->copy();
    }
    else {
        o1->rhs = o2->copy();
        return o1->copy();
    }
}
