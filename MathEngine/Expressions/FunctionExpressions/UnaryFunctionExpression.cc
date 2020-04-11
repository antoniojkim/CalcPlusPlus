
#include <utility>

#include "../../Utils/exceptions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;

UnaryFunctionExpression::UnaryFunctionExpression(const std::string& name, expression&& arg):
    UnaryFunctionExpression{getFunctionIndex(name), std::move(arg)} {
    if (functionIndex == -1){
        throw Exception("Invalid Unary Function: ", name);
    }
}
UnaryFunctionExpression::UnaryFunctionExpression(int functionIndex, expression&& arg):
    functionIndex{functionIndex},
    f{functionIndex != -1 ? get_unary_function(functionIndex) : nullptr},
    arg{std::move(arg)} {}

expression UnaryFunctionExpression::simplify() {
    return make_unique<UnaryFunctionExpression>(functionIndex, arg->simplify());
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

bool UnaryFunctionExpression::isComplex(){ return arg->isComplex(); }

expression UnaryFunctionExpression::copy() {
    return make_unique<UnaryFunctionExpression>(functionIndex, arg->copy());
}

std::ostream& UnaryFunctionExpression::print(std::ostream& out) {
    out << functionNames[functionIndex] << "(";
    return arg->print(out) << ")";
}
std::ostream& UnaryFunctionExpression::postfix(std::ostream& out) {
    return arg->postfix(out) << " " << functionNames[functionIndex];
}


