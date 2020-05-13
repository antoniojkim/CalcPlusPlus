
#include <memory>
#include <utility>

#include "../../Utils/exceptions.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;

UnaryFunctionExpression::UnaryFunctionExpression(const char * name, const expression arg):
    functionIndex{Function::indexOf(name)},
    arg{arg} {
    if (functionIndex == -1){
        throw Exception("Invalid Unary Function: ", std::string{name});
    }

}
UnaryFunctionExpression::UnaryFunctionExpression(std::string& name, const expression arg):
    UnaryFunctionExpression{name.c_str(), arg} {}
UnaryFunctionExpression::UnaryFunctionExpression(int functionIndex, const expression arg):
    functionIndex{functionIndex},
    arg{arg} {}


expression UnaryFunctionExpression::construct(const char * name, const expression arg){
    return shared_ptr<UnaryFunctionExpression>(new UnaryFunctionExpression(name, arg));
}
expression UnaryFunctionExpression::construct(std::string& name, const expression arg){
    return shared_ptr<UnaryFunctionExpression>(new UnaryFunctionExpression(name, arg));
}
expression UnaryFunctionExpression::construct(int functionIndex, const expression arg){
    return shared_ptr<UnaryFunctionExpression>(new UnaryFunctionExpression(functionIndex, arg));
}


expression UnaryFunctionExpression::simplify() {
    return UnaryFunctionExpression::construct(functionIndex, arg->simplify());
}
expression UnaryFunctionExpression::derivative(const std::string& var) {
    auto fprime = get_unary_function_derivative(functionIndex);
    if (fprime){ return fprime(arg, var) * arg->derivative(var); }
    return InvalidExpression::construct(Exception("Unimplemented Error: UnaryFunctionExpression::derivative"));
}
expression UnaryFunctionExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: UnaryFunctionExpression::integrate"));
}

bool UnaryFunctionExpression::evaluable() const { return arg->evaluable(); }

expression UnaryFunctionExpression::evaluate(const Variables& vars) {
    auto fe = get_unary_function_expr(functionIndex);
    if (fe){ return fe(arg, vars); }

    return NumExpression::construct(value(vars));
}

double UnaryFunctionExpression::value(const Variables& vars) const {
    auto f = get_unary_function(functionIndex);
    if (f){ return f(arg->value(vars)); }

    auto fe = get_unary_function_expr(functionIndex);
    if (fe){ return fe(arg, vars)->value(); }

    return GSL_NAN;
}

bool UnaryFunctionExpression::isComplex() const { return arg->isComplex(); }

std::ostream& UnaryFunctionExpression::print(std::ostream& out) const {
    out << Function::names[functionIndex] << "(";
    return arg->print(out) << ")";
}
std::ostream& UnaryFunctionExpression::postfix(std::ostream& out) const {
    return arg->postfix(out) << " " << Function::names[functionIndex];
}
