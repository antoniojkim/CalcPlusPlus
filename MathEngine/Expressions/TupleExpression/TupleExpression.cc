
#include <list>
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../NumericalExpression.h"
#include "../TupleExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

TupleExpression::TupleExpression(){}
TupleExpression::TupleExpression(std::list<expression>&& tuple): _data{std::move(tuple)} {}
TupleExpression::TupleExpression(std::initializer_list<double> tuple) {
    for (auto val : tuple){
        this->_data.emplace_back(NumExpression::construct(val));
    }
}
TupleExpression::TupleExpression(std::initializer_list<gsl_complex> tuple) {
    for (auto val : tuple){
        this->_data.emplace_back(NumExpression::construct(val));
    }
}

expression TupleExpression::construct(){
    return unique_ptr<TupleExpression>(new TupleExpression());
}
expression TupleExpression::construct(std::list<expression>&& tuple){
    return unique_ptr<TupleExpression>(new TupleExpression(std::move(tuple)));
}
expression TupleExpression::construct(std::initializer_list<double> tuple){
    return unique_ptr<TupleExpression>(new TupleExpression(std::forward<std::initializer_list<double>>(tuple)));
}
expression TupleExpression::construct(std::initializer_list<gsl_complex> tuple){
    return unique_ptr<TupleExpression>(new TupleExpression(std::forward<std::initializer_list<gsl_complex>>(tuple)));
}

expression TupleExpression::simplify() {
    return copy();
}
expression TupleExpression::derivative(const std::string& var) {
    list<expression> derivatives;
    for (auto& expr : _data){
        derivatives.emplace_back(expr->derivative(var));
    }
    return TupleExpression::construct(std::move(derivatives));
}
expression TupleExpression::integrate(const std::string& var) {
    list<expression> integrals;
    for (auto& expr : _data){
        integrals.emplace_back(expr->integrate(var));
    }
    return TupleExpression::construct(std::move(integrals));
}

bool TupleExpression::evaluable(){
    for(auto& expr : _data){
        if (!expr->evaluable()){
            return false;
        }
    }
    return true;
}

expression TupleExpression::evaluate(const Variables& vars){
    list<expression> evaluated;
    for (auto& expr : _data){
        evaluated.emplace_back(expr->evaluate(vars));
    }
    return TupleExpression::construct(std::move(evaluated));
}

double TupleExpression::value(const Variables& vars) { return GSL_NAN; }

bool TupleExpression::isComplex(){
    for(auto& expr : _data){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}

expression TupleExpression::copy() {
    list<expression> tupleCopy;
    for (auto& expr : _data){
        tupleCopy.emplace_back(expr->copy());
    }
    return TupleExpression::construct(std::move(tupleCopy));
}

std::ostream& TupleExpression::print(std::ostream& out) {
    out << "(";
    if (!_data.empty()){
        auto expr = _data.begin();
        auto end = _data.end();
        (*(expr++))->print(out);
        while(expr != end){
            (*(expr++))->print(out << ", ");
        }
    }
    return out << ")";
}
std::ostream& TupleExpression::postfix(std::ostream& out) {
    for (auto& expr : _data){
        expr->postfix(out) << " ";
    }
    return out << "tuple_" << _data.size();
}
