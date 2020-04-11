
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;

const Variables emptyVars;

MultiFunctionExpression::MultiFunctionExpression(const std::string& name, std::list<expression>&& args):
    MultiFunctionExpression{getFunctionIndex(name), std::move(args)} {
    if (functionIndex == -1){
        throw Exception("Invalid Unary Function: ", name);
    }
}
MultiFunctionExpression::MultiFunctionExpression(int functionIndex, std::list<expression>&& args):
    functionIndex{functionIndex},
    f{functionIndex != -1 ? get_multi_function(functionIndex) : nullptr},
    fe{functionIndex != -1 ? get_multi_function_expr(functionIndex) : nullptr},
    args{std::move(args)} {}


expression MultiFunctionExpression::simplify() {
    throw Exception("Unimplemented Error: MultiFunctionExpression::simplify");
}
expression MultiFunctionExpression::derivative(const std::string& var) {
    throw Exception("Unimplemented Error: MultiFunctionExpression::derivative");
    // return make_unique<MultiplicationExpression>(
    //     make_unique<MultiFunctionExpression>(fprime, arg->copy()),
    //     arg->derivative(var)
    // );
}
expression MultiFunctionExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: MultiFunctionExpression::integrate");
    // return make_unique<MultiFunctionExpression>(
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


expression MultiFunctionExpression::evaluate() {
    if (fe){
        return fe(args, emptyVars);
    }
    return make_unique<NumExpression>(value());
}
expression MultiFunctionExpression::evaluate(const Variables& vars) {
    if (fe){
        return fe(args, vars);
    }
    return make_unique<NumExpression>(value(vars));
}

double MultiFunctionExpression::value() {
    if (f){
        return f(args, emptyVars);
    }
    return GSL_NAN;
}
double MultiFunctionExpression::value(const Variables& vars) {
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
    return make_unique<MultiFunctionExpression>(functionIndex, std::move(new_args));
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


