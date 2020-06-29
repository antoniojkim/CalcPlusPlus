#include <iostream>
#include <string>

#include <gsl/gsl_math.h>

#include "../Expressions/Expression.h"
#include "../Expressions/FunctionExpression.h"
#include "../Expressions/NumericalExpression.h"
#include "../Scanner/scanner.h"
#include "../Utils/exceptions.h"
#include "AbstractFunction.h"

using namespace std;
using namespace Scanner;

Function::AbstractFunction(const std::string& name, const std::string& signature):
    index{Functions::indexOf(name)}, signature(signature) {}

expression Function::AbstractFunction::eval(expression e, const Variables& vars){
    auto args = signature.parse(e->eval(vars));
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return eval(*args);
}
double value(expression e, const Variables& vars){
    auto args = signature.parse(e->eval(vars));
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return eval(*args)->value();
}
double value(Function::Args& args){ return value(args["x"]->value()); }

expression Function::AbstractFunction::derivative(expression e, const std::string& var){
    auto args = signature.parse(e);
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return derivative(*args, var);
}
expression Function::AbstractFunction::derivative(Function::Args& args, const std::string& var){
    throw Exception("Not Differentiable: ", args);
}
expression Function::AbstractFunction::integral(expression e, const std::string& var){
    throw Exception("Not Integrable: ", e);
}

std::ostream& Function::AbstractFunction::print(std::ostream& out, expression e) {
    auto args = signature.parse(e);
    if (!args){
        throw Exception("Invalid Arguments: ", e);
    }
    return print(out, *args);
}
std::ostream& Function::AbstractFunction::print(std::ostream& out, Function::Args& args) {
    return out << Functions::names[index] << args;
}

Function::ValueFunction::ValueFunction(const std::string& name, DoubleFunction f = nullptr):
    AbstractFunction(name, "(x,)"), f{f} {}
expression Function::ValueFunction::eval(Function::Args& args){
    auto x = args["x"];
    if (x == VAR){
        return FunctionExpression::construct(index, x);
    }
    return NumExpression::construct(value(x->value()));
}


Function::OperatorFunction::OperatorFunction(const char* name): AbstractFunction(name, "(l, r)") {}
std::ostream& Function::OperatorFunction::print(std::ostream& out, Function::Args& args) override {
    return out << "(" << args["l"] << ")" << Functions::names[index] << "(" << args["r"] << ")";
}
