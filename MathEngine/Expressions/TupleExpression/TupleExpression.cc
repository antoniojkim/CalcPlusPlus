
#include <list>
#include <utility>

#include <gsl/gsl_math.h>

#include "../NumericalExpression.h"
#include "../TupleExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

TupleExpression::TupleExpression(){}
TupleExpression::TupleExpression(std::list<expression>&& tuple): tuple{std::move(tuple)} {}
TupleExpression::TupleExpression(std::initializer_list<double> tuple) {
    for (auto val : tuple){
        this->tuple.emplace_back(make_unique<NumExpression>(val));
    }
}
TupleExpression::TupleExpression(std::initializer_list<gsl_complex> tuple) {
    for (auto val : tuple){
        this->tuple.emplace_back(make_unique<NumExpression>(val));
    }
}

expression TupleExpression::simplify() {
    return copy();
}
expression TupleExpression::derivative(const std::string& var) {
    list<expression> derivatives;
    for (auto& expr : tuple){
        derivatives.emplace_back(expr->derivative(var));
    }
    return make_unique<TupleExpression>(std::move(derivatives));
}
expression TupleExpression::integrate(const std::string& var) {
    list<expression> integrals;
    for (auto& expr : tuple){
        integrals.emplace_back(expr->integrate(var));
    }
    return make_unique<TupleExpression>(std::move(integrals));
}

bool TupleExpression::evaluable(){
    for(auto& expr: tuple){
        if (!expr->evaluable()){
            return false;
        }
    }
    return true;
}

double TupleExpression::value() { return GSL_NAN; }

double TupleExpression::value(const Variables& vars) { return GSL_NAN; }

bool TupleExpression::isComplex(){
    for(auto& expr: tuple){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}

expression TupleExpression::copy() {
    list<expression> tupleCopy;
    for (auto& expr : tuple){
        tupleCopy.emplace_back(expr->copy());
    }
    return make_unique<TupleExpression>(std::move(tupleCopy));
}

std::ostream& TupleExpression::print(std::ostream& out) {
    out << "(";
    auto expr = tuple.begin();
    auto end = tuple.end();
    (*(expr++))->print(out);
    while(expr != end){
        (*(expr++))->print(out << ", ");
    }
    return out << ")";
}
std::ostream& TupleExpression::postfix(std::ostream& out) {
    for (auto& expr: tuple){
        expr->postfix(out) << " ";
    }
    for (unsigned int i = 1; i < tuple.size(); ++i){
        out << ", ";
    }
    return out << "tuple";
}
