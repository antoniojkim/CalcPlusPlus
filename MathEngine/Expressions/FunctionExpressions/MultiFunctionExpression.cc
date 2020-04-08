
#include <utility>

#include "../../Utils/exceptions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "MultiFunctionDirectory.h"

using namespace std;

MultiFunctionExpression::MultiFunctionExpression(const std::string& name, std::list<expression>&& args):
    MultiFunctionExpression{getFunctionIndex(name), std::move(args)} {
    if (functionIndex == -1){
        throw Exception("Invalid Unary Function: ", name);
    }
}
MultiFunctionExpression::MultiFunctionExpression(int functionIndex, std::list<expression>&& args):
    functionIndex{functionIndex},
    f{functionIndex != -1 ? get_multi_function(functionIndex) : nullptr},
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

double MultiFunctionExpression::value() { return f(args); }
double MultiFunctionExpression::value(const Variables& vars) {
    list<expression> evaluated_args;
    for (auto& arg: args){
        evaluated_args.emplace_back(arg->evaluate(vars));
    }
    return f(evaluated_args);
}

bool MultiFunctionExpression::complex(){    
    for(auto& arg: args){
        if (arg->complex()){
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


