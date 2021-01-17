
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../TupleExpression.h"

using namespace std;
using namespace Scanner;


FunctionExpression::FunctionExpression(int functionIndex, expression arg, std::initializer_list<std::pair<std::string, expression>> signature):
    Expression(FUNCTION), functionIndex(functionIndex) {
    // Parse args
    if (arg != TUPLE){
        arg = TupleExpression::construct({arg});
    }
    if(arg->size() == signature.size()){
        bool onlyEmpty = true;
        for (auto e : *arg){
            if (e != EMPTY){
                onlyEmpty = false;
                break;
            }
        }
        if (onlyEmpty){ // Most cases should go here
            this->arg = arg;
            return;
        }
    }

    std::vector<expression> positionalArgs;
    positionalArgs.reserve(arg->size());

    int eIndex = 0;

    // Get Positional Args
    while(eIndex < arg->size() && !(arg->at(eIndex) == VAR && arg->at(eIndex)->at(1))){
        positionalArgs.emplace_back(arg->at(eIndex++));
    }

    // Get Keyword Args
    std::map<std::string, expression> kwargs;
    while(eIndex < arg->size()){
        if (arg->at(eIndex) != VAR){
            throw Exception("Positional argument follows keyword argument");
        }
        auto name = arg->at(eIndex)->repr();
        if (kwargs.count(name) > 0){
            throw Exception("Keyword argument repeated: ", arg);
        }
        kwargs[name] = arg->at(eIndex++)->at(1);
    }

    std::vector<expression> args;
    args.reserve(signature.size());

    int pIndex = 0;
    auto s = signature.begin();
    auto end = signature.end();
    while (s != end && s->second == EMPTY && !positionalArgs.empty()){
        if (kwargs.count(s->first) > 0){
            throw Exception(repr(), " got multiple value for argument '", s->first, "'");
        }
        args.emplace_back(positionalArgs.at(0));
        positionalArgs.erase(positionalArgs.begin());
        ++s;
    }

    if (s == end){
        this->arg = TupleExpression::construct(std::move(args));
        return;
    }

    if (s->second == VARARGS){  // Move remaining positional args into varargs
        args.emplace_back(TupleExpression::construct(std::move(positionalArgs)));
        ++s;
    }
    else {
        for(auto p: positionalArgs){
            if (kwargs.count(s->first) > 0){
                throw Exception(repr(), " got multiple value for argument '", s->first, "'");
            }
            args.emplace_back(p);
            ++s;
        }
    }

    while (s != end){
        if (s->second == EMPTY){
            throw Exception(repr(), ": non-default argument follows default argument");
        }
        if (s->second == VARARGS){
            throw Exception(repr(), ": varargs argument follows named argument");
        }
        if (kwargs.count(s->first) > 0){
            args.emplace_back(kwargs.at(s->first));
        }
        else{
            args.emplace_back(s->second);
        }
        ++s;
    }

    this->arg = TupleExpression::construct(std::move(args));
}


expression FunctionExpression::construct(const char * name, expression arg){
    return Functions::construct(Functions::indexOf(name), arg);
}
expression FunctionExpression::construct(std::string& name, expression arg){
    int functionIndex = Functions::indexOf(name);
    if (functionIndex < 0){
        throw Exception("Invalid Function: ", name);
    }
    return Functions::construct(Functions::indexOf(name), arg);
}
expression FunctionExpression::construct(int functionIndex, expression arg){
    return Functions::construct(functionIndex, arg);
}
expression FunctionExpression::construct(const char * name, std::initializer_list<expression> args){
    return Functions::construct(
        Functions::indexOf(name),
        TupleExpression::construct(std::forward<std::initializer_list<expression>>(args))
    );
}
expression FunctionExpression::construct(std::string& name, std::initializer_list<expression> args){
    return Functions::construct(
        Functions::indexOf(name),
        TupleExpression::construct(std::forward<std::initializer_list<expression>>(args))
    );
}
expression FunctionExpression::construct(int functionIndex, std::initializer_list<expression> args){
    return Functions::construct(
        functionIndex,
        TupleExpression::construct(std::forward<std::initializer_list<expression>>(args))
    );
}

bool FunctionExpression::isComplex() const {
    return arg->isComplex();
}
bool FunctionExpression::isEvaluable(const Variables& vars) const {
    return arg->isEvaluable(vars);
}

expression FunctionExpression::eval(const Variables& vars){
    if (!arg->isEvaluable()){
        return FunctionExpression::construct(functionIndex, arg->eval(vars));
    }
    return NumExpression::construct(value(vars));
}

bool FunctionExpression::equals(expression e, double precision) const {
    if (e == FUNCTION && functionIndex == e->id()){
        return arg->equals(e->at(1), precision);
    }
    return false;
}

expression FunctionExpression::at(const int index) {
    switch (index){
        case 0: return copy();
        case 1: return arg;
        default: throw Exception("FunctionExpression::at: Index out of bounds");
    }
}

std::string FunctionExpression::repr() const {
    return Functions::names[functionIndex];
}
int FunctionExpression::id() const {
    return functionIndex;
}

std::ostream& FunctionExpression::print(std::ostream& out, const bool pretty) const {
    out << Functions::names[functionIndex];
    return arg->print(out, pretty);
}
std::ostream& FunctionExpression::postfix(std::ostream& out) const {
    if (arg->size() == 1){
        arg->at(0)->postfix(out);
    }
    else{
        arg->postfix(out);
    }
    return out << " " << Functions::names[functionIndex];
}
