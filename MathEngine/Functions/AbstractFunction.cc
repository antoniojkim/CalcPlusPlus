#include <iostream>
#include <string>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/FunctionExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Scanner/scanner.h"
#include "../Utils/Exception.h"
#include "AbstractFunction.h"
#include "Functions.h"

using namespace std;
using namespace Scanner;

Function::AbstractFunction::AbstractFunction(const std::string& name, const std::string& signature):
    index(Functions::indexOf(name)), signature(signature) {}

expression Function::AbstractFunction::eval(expression e, const Variables& vars) const {
    auto args = signature.parse(e->eval(vars));
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return eval(*args);
}
double Function::AbstractFunction::value(expression e, const Variables& vars) const {
    auto args = signature.parse(e->eval(vars));
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return eval(*args)->value();
}
double Function::AbstractFunction::value(Function::Args& args) const {
    return value(args["x"]->value());
}

expression Function::AbstractFunction::derivative(expression e, const std::string& var) const {
    auto args = signature.parse(e);
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return derivative(*args, var);
}
expression Function::AbstractFunction::derivative(Function::Args& args, const std::string& var) const {
    throw Exception("Not Differentiable: ", args);
}

expression Function::AbstractFunction::integrate(expression e, const std::string& var) const {
    auto args = signature.parse(e);
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return integrate(*args, var);
}
expression Function::AbstractFunction::integrate(Function::Args& args, const std::string& var) const {
    throw Exception("Not Integrable: ", args);
}

std::ostream& Function::AbstractFunction::print(std::ostream& out, expression e) const {
    auto args = signature.parse(e);
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return print(out, *args);
}
std::ostream& Function::AbstractFunction::print(std::ostream& out, Function::Args& args) const {
    return out << Functions::names[index] << args;
}

Function::ValueFunction::ValueFunction(const std::string& name, DoubleFunction f):
    AbstractFunction(name, "(x,)"), f{f} {}
expression Function::ValueFunction::eval(Function::Args& args) const {
    auto x = args["x"];
    if (x == VAR){
        return FunctionExpression::construct(index, x);
    }
    return NumExpression::construct(value(x->value()));
}


Function::OperatorFunction::OperatorFunction(const char* name): AbstractFunction(name, "(l, r)") {}
std::ostream& Function::OperatorFunction::print(std::ostream& out, Function::Args& args) const {
    return out << "(" << args["l"] << ")" << Functions::names[index] << "(" << args["r"] << ")";
}
