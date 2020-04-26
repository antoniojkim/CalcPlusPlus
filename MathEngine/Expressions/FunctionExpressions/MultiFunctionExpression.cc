
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;

MultiFunctionExpression::MultiFunctionExpression(const char * name, std::list<expression>&& args):
    MultiFunctionExpression{getFunctionIndex(name), std::move(args)} {
    if (functionIndex == -1){
        throw Exception("Invalid Unary Function: ", name);
    }
}
MultiFunctionExpression::MultiFunctionExpression(std::string& name, std::list<expression>&& args):
    MultiFunctionExpression{name.c_str(), std::move(args)} {}
MultiFunctionExpression::MultiFunctionExpression(int functionIndex, std::list<expression>&& args):
    functionIndex{functionIndex},
    args{std::move(args)} {}


expression MultiFunctionExpression::construct(const char * name, std::list<expression>&& args){
    return unique_ptr<MultiFunctionExpression>(new MultiFunctionExpression(name, std::move(args)));
}
expression MultiFunctionExpression::construct(std::string& name, std::list<expression>&& args){
    return unique_ptr<MultiFunctionExpression>(new MultiFunctionExpression(name, std::move(args)));
}
expression MultiFunctionExpression::construct(int functionIndex, std::list<expression>&& args){
    return unique_ptr<MultiFunctionExpression>(new MultiFunctionExpression(functionIndex, std::move(args)));
}


expression MultiFunctionExpression::simplify() {
    throw Exception("Unimplemented Error: MultiFunctionExpression::simplify");
}
expression MultiFunctionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: MultiFunctionExpression::derivative");
    // return make_unique<MultiplicationExpression>(
    //     MultiFunctionExpression::construct(fprime, arg->copy()),
    //     arg->derivative(var)
    // );
}
expression MultiFunctionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: MultiFunctionExpression::integrate");
    // return MultiFunctionExpression::construct(
    //     lhs->integrate(var),
    //     rhs->integrate(var)
    // );
}

bool MultiFunctionExpression::evaluable(){
    for(auto& arg: args){
        if (!arg->evaluable()){
            return false;
        }
    }
    return true;
}


expression MultiFunctionExpression::evaluate(const Variables& vars) {
    auto fe = get_multi_function_expr(functionIndex);
    if (fe){
        return fe(args, vars);
    }
    return NumExpression::construct(value(vars));
}

double MultiFunctionExpression::value(const Variables& vars) {
    auto f = get_multi_function(functionIndex);
    if (f){
        return f(args, vars);
    }
    return GSL_NAN;
}

bool MultiFunctionExpression::isComplex(){
    for(auto& arg: args){
        if (arg->isComplex()){
            return true;
        }
    }
    return false;
}

expression MultiFunctionExpression::copy() {
    list<expression> new_args;
    for(auto& arg: args){
        new_args.emplace_back(arg->copy());
    }
    return MultiFunctionExpression::construct(functionIndex, std::move(new_args));
}

std::ostream& MultiFunctionExpression::print(std::ostream& out) {
    out << functionNames[functionIndex] << "(";
    auto arg = args.begin();
    auto end = args.end();
    (*(arg++))->print(out);
    while (arg != end){
        out << ", ";
        (*(arg++))->print(out);
    }
    return out << ")";
}
std::ostream& MultiFunctionExpression::postfix(std::ostream& out) {
    for (auto& arg: args){
        arg->postfix(out) << " ";
    }
    for (unsigned int i = 1; i < args.size(); ++i){
        out << ", ";
    }
    return out << functionNames[functionIndex];
}
