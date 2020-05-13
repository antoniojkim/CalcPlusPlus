
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Utils/exceptions.h"
#include "../FunctionExpression.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "Functions.h"
#include "FunctionDirectory.h"

using namespace std;

MultiFunctionExpression::MultiFunctionExpression(const char * name, std::list<expression>&& args):
    MultiFunctionExpression{Function::indexOf(name), std::move(args)} {
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
    return shared_ptr<MultiFunctionExpression>(new MultiFunctionExpression(name, std::move(args)));
}
expression MultiFunctionExpression::construct(std::string& name, std::list<expression>&& args){
    return shared_ptr<MultiFunctionExpression>(new MultiFunctionExpression(name, std::move(args)));
}
expression MultiFunctionExpression::construct(int functionIndex, std::list<expression>&& args){
    return shared_ptr<MultiFunctionExpression>(new MultiFunctionExpression(functionIndex, std::move(args)));
}


expression MultiFunctionExpression::simplify() {
    return InvalidExpression::construct(Exception("Unimplemented Error: MultiFunctionExpression::simplify"));
}
expression MultiFunctionExpression::derivative(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: MultiFunctionExpression::derivative"));
}
expression MultiFunctionExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: MultiFunctionExpression::integrate"));
}

bool MultiFunctionExpression::evaluable() const {
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

double MultiFunctionExpression::value(const Variables& vars) const {
    auto f = get_multi_function(functionIndex);
    if (f){
        return f(args, vars);
    }
    return GSL_NAN;
}

bool MultiFunctionExpression::isComplex() const {
    for(auto& arg: args){
        if (arg->isComplex()){
            return true;
        }
    }
    return false;
}

std::ostream& MultiFunctionExpression::print(std::ostream& out) const {
    out << Function::names[functionIndex] << "(";
    if (args.size() > 0){
        auto arg = args.begin();
        auto end = args.end();
        (*(arg++))->print(out);
        while (arg != end){
            out << ", ";
            (*(arg++))->print(out);
        }
    }
    return out << ")";
}
std::ostream& MultiFunctionExpression::postfix(std::ostream& out) const {
    for (auto& arg: args){
        arg->postfix(out) << " ";
    }
    for (unsigned int i = 1; i < args.size(); ++i){
        out << ", ";
    }
    return out << Function::names[functionIndex];
}
