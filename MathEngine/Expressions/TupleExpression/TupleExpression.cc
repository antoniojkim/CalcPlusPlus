
#include <list>
#include <memory>
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
        this->data.emplace_back(NumExpression::construct(val));
    }
}
TupleExpression::TupleExpression(std::initializer_list<gsl_complex> tuple) {
    for (auto val : tuple){
        this->data.emplace_back(NumExpression::construct(val));
    }
}

HeapArray<double> TupleExpression::array(const Variables& vars){
    HeapArray<double> a(data.size());
    int i = 0;
    for (auto& e : data){
        a[i++] = e->value(vars);
    }
    return a;
}
void TupleExpression::array(double* a, size_t size, const Variables& vars){
    if (size <= data.size()){
        auto arg = std::begin(data);
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

expression TupleExpression::simplify() {
    list<expression> simplified;
    for (auto& expr : data){
        simplified.emplace_back(expr->simplify());
    }
    return TupleExpression::construct(std::move(simplified));
}
expression TupleExpression::derivative(const std::string& var) {
    list<expression> derivatives;
    for (auto& expr : data){
        derivatives.emplace_back(expr->derivative(var));
    }
    return TupleExpression::construct(std::move(derivatives));
}
expression TupleExpression::integrate(const std::string& var) {
    list<expression> integrals;
    for (auto& expr : data){
        integrals.emplace_back(expr->integrate(var));
    }
    return TupleExpression::construct(std::move(integrals));
}

bool TupleExpression::evaluable() const {
    for(auto& expr : data){
        if (!expr->evaluable()){
            return false;
        }
    }
    return true;
}

expression TupleExpression::evaluate(const Variables& vars) {
    list<expression> evaluated;
    for (auto& expr : data){
        evaluated.emplace_back(expr->evaluate(vars));
    }
    return TupleExpression::construct(std::move(evaluated));
}

double TupleExpression::value(const Variables& vars) const { return GSL_NAN; }

bool TupleExpression::isComplex() const {
    for(auto& expr : data){
        if (expr->isComplex()){
            return true;
        }
    }
    return false;
}

bool TupleExpression::isEqual(expression e, double precision) const {
    auto t = e->tuple();
    if (t){
        if (data.size() == t->data.size()){
            if (data.size() > 0){
                auto b1 = data.begin();
                auto e1 = data.end();
                auto b2 = t->data.begin();
                auto e2 = t->data.end();
                while (b1 != e1 && b2 != e2){
                    if (!(*b1)->isEqual(*b2, precision)){
                        return false;
                    }
                    ++b1;
                    ++b2;
                }
            }
            return true;
        }
    }
    return false;
}

std::ostream& TupleExpression::print(std::ostream& out) const {
    out << "(";
    if (!data.empty()){
        auto expr = data.begin();
        auto end = data.end();
        (*(expr++))->print(out);
        if (expr == end){
            out << ",";
        }
        while(expr != end){
            (*(expr++))->print(out << ", ");
        }
    }
    return out << ")";
}
std::ostream& TupleExpression::postfix(std::ostream& out) const {
    out << "(";
    if (!data.empty()){
        auto expr = data.begin();
        auto end = data.end();
        (*(expr++))->postfix(out);
        if (expr == end){
            out << ",";
        }
        while(expr != end){
            (*(expr++))->postfix(out << ", ");
        }
    }
    return out << ")";
}
