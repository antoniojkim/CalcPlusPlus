
#include <memory>
#include <utility>

#include "../../Utils/exceptions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;

UnaryFunctionExpression::UnaryFunctionExpression(const char * name, expression&& arg):
    functionIndex{getFunctionIndex(name)},
    arg{std::move(arg)} {
    if (functionIndex == -1){
        throw Exception("Invalid Unary Function: ", std::string{name});
    }
}
UnaryFunctionExpression::UnaryFunctionExpression(std::string& name, expression&& arg):
    UnaryFunctionExpression{name.c_str(), std::move(arg)} {}
UnaryFunctionExpression::UnaryFunctionExpression(int functionIndex, expression&& arg):
    functionIndex{functionIndex},
    arg{std::move(arg)} {}


expression UnaryFunctionExpression::construct(const char * name, expression&& arg){
    return unique_ptr<UnaryFunctionExpression>(new UnaryFunctionExpression(name, std::move(arg)));
}
expression UnaryFunctionExpression::construct(std::string& name, expression&& arg){
    return unique_ptr<UnaryFunctionExpression>(new UnaryFunctionExpression(name, std::move(arg)));
}
expression UnaryFunctionExpression::construct(int functionIndex, expression&& arg){
    return unique_ptr<UnaryFunctionExpression>(new UnaryFunctionExpression(functionIndex, std::move(arg)));
}


expression UnaryFunctionExpression::simplify() {
    return UnaryFunctionExpression::construct(functionIndex, arg->simplify());
}
expression UnaryFunctionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: UnaryFunctionExpression::derivative");
    // return make_unique<MultiplicationExpression>(
    //     UnaryFunctionExpression::construct(fprime, arg->copy()),
    //     arg->derivative(var)
    // );
}
expression UnaryFunctionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: UnaryFunctionExpression::integrate");
    // return UnaryFunctionExpression::construct(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool UnaryFunctionExpression::evaluable(){ return arg->evaluable(); }

expression UnaryFunctionExpression::evaluate(const Variables& vars) {
    auto fe = get_unary_function_expr(functionIndex);
    if (fe){ return fe(arg, vars); }

    return NumExpression::construct(value(vars));
}

double UnaryFunctionExpression::value(const Variables& vars) {
    auto f = get_unary_function(functionIndex);
    if (f){ return f(arg->value(vars)); }

    auto fe = get_unary_function_expr(functionIndex);
    if (fe){ return fe(arg, vars)->value(); }

    return GSL_NAN;
}

bool UnaryFunctionExpression::isComplex(){ return arg->isComplex(); }

expression UnaryFunctionExpression::copy() {
    return UnaryFunctionExpression::construct(functionIndex, arg->copy());
}

std::ostream& UnaryFunctionExpression::print(std::ostream& out) {
    out << functionNames[functionIndex] << "(";
    return arg->print(out) << ")";
}
std::ostream& UnaryFunctionExpression::postfix(std::ostream& out) {
    return arg->postfix(out) << " " << functionNames[functionIndex];
}
