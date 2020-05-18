
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

DynamicArray<double> TupleExpression::array(const Variables& vars){
    DynamicArray<double> a(_data.size());
    int i = 0;
    for (auto& e : _data){
        a[i++] = e->value(vars);
    }
    return a;
}
void TupleExpression::array(double* a, size_t size, const Variables& vars){
    if (size <= _data.size()){
        auto arg = std::begin(_data);
        for (size_t i = 0; i < size; ++i){
            a[i] = (*(arg++))->value(vars);
        }
    }
}

expression TupleExpression::construct(){
    return shared_ptr<TupleExpression>(new TupleExpression());
}
expression TupleExpression::construct(std::list<expression>&& tuple){
    return shared_ptr<TupleExpression>(new TupleExpression(std::move(tuple)));
}
expression TupleExpression::construct(std::initializer_list<double> tuple){
    return shared_ptr<TupleExpression>(new TupleExpression(std::forward<std::initializer_list<double>>(tuple)));
}
expression TupleExpression::construct(std::initializer_list<gsl_complex> tuple){
    return shared_ptr<TupleExpression>(new TupleExpression(std::forward<std::initializer_list<gsl_complex>>(tuple)));
}

expression TupleExpression::simplify() { return copy(); }
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

bool TupleExpression::evaluable() const {
    for(auto& expr : _data){
        if (!expr->evaluable()){
            return false;
        }
    }
    return true;
}

expression TupleExpression::evaluate(const Variables& vars) {
    list<expression> evaluated;
    for (auto& expr : _data){
        evaluated.emplace_back(expr->evaluate(vars));
    }
    return TupleExpression::construct(std::move(evaluated));
}

double TupleExpression::value(const Variables& vars) const { return GSL_NAN; }

bool TupleExpression::isComplex() const {
    for(auto& expr : _data){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}

std::ostream& TupleExpression::print(std::ostream& out) const {
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
std::ostream& TupleExpression::postfix(std::ostream& out) const {
    out << "(";
    if (!_data.empty()){
        auto expr = _data.begin();
        auto end = _data.end();
        (*(expr++))->postfix(out);
        while(expr != end){
            (*(expr++))->postfix(out << ", ");
        }
    }
    return out << ")";
}
