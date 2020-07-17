
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


FunctionExpression::FunctionExpression(int functionIndex, expression arg, int numPositional, bool hasVarArgs, std::initializer_list<std::pair<std::string, expression>> defaultArgs):
    Expression(FUNCTION), functionIndex(functionIndex) {
    // Parse args
    int numArgs = numPositional + (hasVarArgs ? 1 : 0) + defaultArgs.size();
    if (arg->size() < numPositional){
        throw Exception("Not enough many arguments given for ", repr(), ": ", arg);
    }
    if (arg->size() > numArgs){
        throw Exception("Too many arguments given for ", repr(), ": ", arg);
    }

    if (arg != TUPLE){
        if (numArgs == 1){
            this->arg = arg;
        }
        else{
            throw Exception(repr(), " expected a tuple. Got: ", arg);
        }
    }
    else if(arg->size() == numPositional && !hasVarArgs && defaultArgs.size() == 0){
        this->arg = arg;
    }
    else{
        std::vector<expression> args;
        args.reserve(numArgs);

        int eIndex = 0;
        for (int i = 0; i < numPositional; ++i){
            args.emplace_back(arg->at(eIndex++));
        }
        if (hasVarArgs){
            std::vector<expression> vararg;
            vararg.reserve(arg->size() - eIndex);
            while(eIndex < arg->size() && arg->at(eIndex) != VAR){
                vararg.emplace_back(arg->at(eIndex++));
            }
            args.emplace_back(TupleExpression::construct(std::move(vararg)));
        }
        std::map<std::string, expression> kwargs;
        while(eIndex < arg->size()){
            if (arg->at(eIndex) != VAR){
                throw Exception("Positional argument follows keyword argument");
            }
            auto name = arg->at(eIndex)->repr();
            if (kwargs.count(name) > 0){
                throw Exception("Keyword argument repeated: ", arg);
            }
            kwargs[name] = arg->at(eIndex++)->at(0);
        }
        for (auto& defaultArg : defaultArgs){
            if (kwargs.count(defaultArg.first) > 0){
                args.emplace_back(kwargs.at(defaultArg.first));
            }
            else{
                args.emplace_back(defaultArg.second);
            }
        }

        this->arg = TupleExpression::construct(std::move(args));
    }

}


expression FunctionExpression::construct(const char * name, expression arg){
    return Functions::construct(Functions::indexOf(name), arg);
}
expression FunctionExpression::construct(std::string& name, expression arg){
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
        return ValueFunctionExpression::construct(functionIndex, f, arg->eval(vars));
    }
    return NumExpression::construct(value(vars));
}

bool FunctionExpression::equals(expression e, double precision) const {
    if (e == FUNCTION && functionIndex == e->id()){
        return arg->equals(e->at(0), precision);
    }
    return false;
}

expression FunctionExpression::at(const int index) {
    if (index == 0){
        return copy();
    }
    return arg->at(index - 1);
}

std::string FunctionExpression::repr() const {
    return Functions::names[functionIndex];
}
int FunctionExpression::id() const {
    return functionIndex;
}

std::ostream& FunctionExpression::print(std::ostream& out, const bool pretty) const {
    out << Functions::names[functionIndex];
    if (arg == TUPLE){
        return arg->print(out, pretty);
    }
    return arg->print(out << "(", pretty) << ")";
}
std::ostream& FunctionExpression::postfix(std::ostream& out) const {
    arg->postfix(out) << " ";
    return out << Functions::names[functionIndex];
}
