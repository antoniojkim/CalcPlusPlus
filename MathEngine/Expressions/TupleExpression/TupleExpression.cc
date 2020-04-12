
#include <list>
#include <utility>

#include <gsl/gsl_math.h>

#include "../NumericalExpression.h"
#include "../TupleExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

TupleExpression::TupleExpression(){}
TupleExpression::TupleExpression(std::list<expression>&& tuple): data{std::move(tuple)} {}
TupleExpression::TupleExpression(std::initializer_list<double> tuple) {
    for (auto val : tuple){
        this->data.emplace_back(make_unique<NumExpression>(val));
    }
}
TupleExpression::TupleExpression(std::initializer_list<gsl_complex> tuple) {
    for (auto val : tuple){
        this->data.emplace_back(make_unique<NumExpression>(val));
    }
}

expression TupleExpression::simplify() {
    return copy();
}
expression TupleExpression::derivative(const std::string& var) {
    list<expression> derivatives;
    for (auto& expr : data){
        derivatives.emplace_back(expr->derivative(var));
    }
    return make_unique<TupleExpression>(std::move(derivatives));
}
expression TupleExpression::integrate(const std::string& var) {
    list<expression> integrals;
    for (auto& expr : data){
        integrals.emplace_back(expr->integrate(var));
    }
    return make_unique<TupleExpression>(std::move(integrals));
}

bool TupleExpression::evaluable(){
    for(auto& expr: data){
        if (!expr->evaluable()){
            return false;
        }
    }
    return true;
}

double TupleExpression::value() { return GSL_NAN; }

double TupleExpression::value(const Variables& vars) { return GSL_NAN; }

bool TupleExpression::isComplex(){
    for(auto& expr: data){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}

expression TupleExpression::copy() {
    list<expression> tupleCopy;
    for (auto& expr : data){
        tupleCopy.emplace_back(expr->copy());
    }
    return make_unique<TupleExpression>(std::move(tupleCopy));
}

std::ostream& TupleExpression::print(std::ostream& out) {
    out << "(";
    if (!data.empty()){
        auto expr = data.begin();
        auto end = data.end();
        (*(expr++))->print(out);
        while(expr != end){
            (*(expr++))->print(out << ", ");
        }
    }
    return out << ")";
}
std::ostream& TupleExpression::postfix(std::ostream& out) {
    for (auto& expr: data){
        expr->postfix(out) << " ";
    }
    return out << "tuple_" << data.size();
}
