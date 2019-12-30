
#include "../FunctionExpression.h"
#include "../BinaryExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

#include <utility>

using namespace std;

UnaryFunctionExpression::UnaryFunctionExpression(const std::string& name, expression&& arg):
    name{name}, f{get_unary_function(name)}, arg{std:move(arg)} {}

expression UnaryFunctionExpression::simplify() {
    return make_unique<UnaryFunctionExpression>(name, arg->simplify());
}
expression UnaryFunctionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: UnaryFunctionExpression::derivative");
    // return make_unique<MultiplicationExpression>(
    //     make_unique<UnaryFunctionExpression>(fprime, arg->copy()),
    //     arg->derivative(var)
    // );
}
expression UnaryFunctionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: UnaryFunctionExpression::integrate");
    // return make_unique<UnaryFunctionExpression>(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool UnaryFunctionExpression::evaluable(){ return arg->evaluable(); }

double UnaryFunctionExpression::value() { return f(arg->value()); }
double UnaryFunctionExpression::value(const Variables& vars) { return f(arg->value(vars)); }

bool UnaryFunctionExpression::complex(){ return arg->complex(); }

expression UnaryFunctionExpression::copy() {
    return make_unique<UnaryFunctionExpression>(name, arg->copy());
}

std::ostream& UnaryFunctionExpression::print(std::ostream& out) {
    out << name << "(";
    return arg->print(out) << ")";
}

