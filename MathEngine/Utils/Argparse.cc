
#include <list>
#include <map>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/NumericalExpression.h"
#include "../Expressions/TupleExpression.h"
#include "../Expressions/VariableExpression.h"
#include "../Parser/modifiedShuntingYard.h"
#include "../Scanner/scanner.h"
#include "../Utils/Exception.h"
#include "Argparse.h"

using namespace std;
using namespace Function;
using namespace Scanner;


Args::Args(int numPositional, bool hasVarArgs, const std::vector<double>& defaultArgs, expression e):
    numPositional{numPositional}, hasVarArgs{hasVarArgs}, defaultArgs{defaultArgs}, e{e}, argIndex{0}, eIndex{0} {}

// TODO: Add support for passing in named arguments
expression Args::next(){
    if (numPositional > 0){
        if (eIndex >= e->size()){
            throw Exception("Not enough arguments provided. Got: ", e);
        }
        --numPositional;
        return e->at(eIndex++);
    }
    else if(hasVarArgs) {
        vector<expression> varargs;
        varargs.reserve(e->size());
        while(eIndex < e->size() && e->at(eIndex) != VAR){
            varargs.emplace_back(e->at(eIndex++));
        }
        hasVarArgs = false;
        return TupleExpression::construct(std::move(varargs));
    }
    else if(argIndex < defaultArgs.size()) {
        if (eIndex >= e->size()){
            if (gsl_isnan(defaultArgs.at(argIndex))){
                return nullptr;
            }
            return NumExpression::construct(defaultArgs.at(argIndex++));
        }
        ++argIndex;
        return e->at(eIndex++);
    }
    throw Exception("Too many arguments given. Got: ", e);
}
double Args::nextValue(){
    return next()->value();
}

const ModifiedShuntingYard parser;

Signature::Signature(int numPositional, bool hasVarArgs, std::initializer_list<double> defaultArgs):
    numPositional{numPositional}, hasVarArgs{hasVarArgs}, defaultArgs{defaultArgs} {}

Function::Args Signature::parse(expression e) const {
    return Function::Args(numPositional, hasVarArgs, defaultArgs, e);
}
