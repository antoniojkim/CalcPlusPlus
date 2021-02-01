
#include <algorithm>
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"
#include "../TupleExpression.h"

using namespace std;
using namespace Scanner;

TupleExpression::TupleExpression() : Expression(TUPLE) {}
TupleExpression::TupleExpression(std::vector<expression>&& tuple) :
    Expression(TUPLE), data(std::move(tuple)) {}
TupleExpression::TupleExpression(std::list<expression>& tuple) : Expression(TUPLE) {
    data.reserve(tuple.size());
    for (auto e : tuple) { this->data.emplace_back(e); }
}
TupleExpression::TupleExpression(std::initializer_list<expression> tuple) :
    Expression(TUPLE) {
    data.reserve(tuple.size());
    for (auto e : tuple) { this->data.emplace_back(e); }
}
TupleExpression::TupleExpression(std::initializer_list<double> tuple) :
    Expression(TUPLE) {
    data.reserve(tuple.size());
    for (auto val : tuple) { this->data.emplace_back(NumExpression::construct(val)); }
}
TupleExpression::TupleExpression(std::initializer_list<gsl_complex> tuple) :
    Expression(TUPLE) {
    data.reserve(tuple.size());
    for (auto val : tuple) { this->data.emplace_back(NumExpression::construct(val)); }
}

expression TupleExpression::simplify() {
    vector<expression> simplified;
    simplified.reserve(data.size());
    for (auto& expr : data) { simplified.emplace_back(expr->simplify()); }
    return TupleExpression::construct(std::move(simplified));
}
expression TupleExpression::derivative(const std::string& var) {
    vector<expression> derivatives;
    derivatives.reserve(data.size());
    for (auto& expr : data) { derivatives.emplace_back(expr->derivative(var)); }
    return TupleExpression::construct(std::move(derivatives));
}
expression TupleExpression::integrate(const std::string& var) {
    vector<expression> integrals;
    integrals.reserve(data.size());
    for (auto& expr : data) { integrals.emplace_back(expr->integrate(var)); }
    return TupleExpression::construct(std::move(integrals));
}

expression TupleExpression::at(const int index) { return data.at(index); }
size_t TupleExpression::size() const { return data.size(); }

expression TupleExpression::apply(TransformerFunction f) {
    std::transform(data.begin(), data.end(), data.begin(), f);
    return copy();
}

bool TupleExpression::isComplex() const {
    for (auto& expr : data) {
        if (expr->isComplex()) { return true; }
    }
    return false;
}
bool TupleExpression::isEvaluable(const Variables& vars) const {
    for (auto& expr : data) {
        if (!expr->isEvaluable(vars)) { return false; }
    }
    return true;
}

expression TupleExpression::eval(const Variables& vars) {
    vector<expression> evaluated;
    evaluated.reserve(data.size());
    for (auto& expr : data) { evaluated.emplace_back(expr->eval(vars)); }
    return TupleExpression::construct(std::move(evaluated));
}
double TupleExpression::value(const Variables& vars) const { return GSL_NAN; }

bool TupleExpression::equals(expression e, double precision) const {
    if (e == TUPLE && data.size() == e->size()) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (!data[i]->equals(e->at(i), precision)) { return false; }
        }
        return true;
    }
    return false;
}

std::ostream& TupleExpression::print(std::ostream& out, const bool pretty) const {
    out << "(";
    if (!data.empty()) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (i != 0) { out << ", "; }
            data[i]->print(out, pretty);
        }
    }
    return out << ")";
}
std::ostream& TupleExpression::postfix(std::ostream& out) const {
    out << "(";
    if (!data.empty()) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (i != 0) { out << ", "; }
            data[i]->postfix(out);
        }
    }
    return out << ")";
}
