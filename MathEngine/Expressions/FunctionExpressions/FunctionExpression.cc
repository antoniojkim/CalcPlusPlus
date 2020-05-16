
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;


FunctionExpression::FunctionExpression(int functionIndex, expression arg):
    functionIndex{functionIndex},
    arg{arg} {

}


expression FunctionExpression::construct(const char * name, expression arg){
    return shared_ptr<FunctionExpression>(new FunctionExpression(Function::indexOf(name), arg));
}
expression FunctionExpression::construct(std::string& name, expression arg){
    return shared_ptr<FunctionExpression>(new FunctionExpression(Function::indexOf(name), arg));
}
expression FunctionExpression::construct(int functionIndex, expression arg){
    return shared_ptr<FunctionExpression>(new FunctionExpression(functionIndex, arg));
}


expression FunctionExpression::simplify() {
    return InvalidExpression::construct(Exception("Unimplemented Error: FunctionExpression::simplify"));
}
expression FunctionExpression::derivative(const std::string& var) {
    auto fprime = get_function_derivative(functionIndex);
    if (fprime){ return fprime(arg, var) * arg->derivative(var); }
    return InvalidExpression::construct(Exception("Unimplemented Error: FunctionExpression::derivative"));
}
expression FunctionExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: FunctionExpression::integrate"));
}

bool FunctionExpression::evaluable() const {
    return arg->evaluable();
}


expression FunctionExpression::evaluate(const Variables& vars) {
    auto fe = get_function_expr(functionIndex);
    if (fe){
        return fe(arg, vars);
    }
    return NumExpression::construct(value(vars));
}

double FunctionExpression::value(const Variables& vars) const {
    auto f = get_function(functionIndex);
    if (f){
        return f(arg, vars);
    }
    return GSL_NAN;
}

bool FunctionExpression::isComplex() const {
    return arg->isComplex();
}

std::ostream& FunctionExpression::print(std::ostream& out) const {
    out << Function::names[functionIndex];
    return arg->print(out);
}
std::ostream& FunctionExpression::postfix(std::ostream& out) const {
    arg->postfix(out) << " ";
    return out << Function::names[functionIndex];
}
