
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../TupleExpression.h"

using namespace std;
using namespace Scanner;


FunctionExpression::FunctionExpression(int functionIndex, const expression arg):
    Expression(FUNCTION), functionIndex(functionIndex), arg(arg) {}


expression FunctionExpression::construct(const char * name, const expression arg){
    return FunctionExpression::construct(Functions::indexOf(name), arg);
}
expression FunctionExpression::construct(std::string& name, const expression arg){
    return FunctionExpression::construct(Functions::indexOf(name), arg);
}
expression FunctionExpression::construct(int functionIndex, const expression arg){
    if (functionIndex < 0){
        throw Exception("Invalid Function");
    }
    if (functionIndex == Functions::indexOf("neg")){
        return -arg;
    }
    return shared_ptr<FunctionExpression>(new FunctionExpression(functionIndex, arg));
}
expression FunctionExpression::construct(const char * name, std::initializer_list<expression> args){
    return FunctionExpression::construct(
        Functions::indexOf(name),
        TupleExpression::construct(std::forward<std::initializer_list<expression>>(args))
    );
}
expression FunctionExpression::construct(std::string& name, std::initializer_list<expression> args){
    return FunctionExpression::construct(
        Functions::indexOf(name),
        TupleExpression::construct(std::forward<std::initializer_list<expression>>(args))
    );
}
expression FunctionExpression::construct(int functionIndex, std::initializer_list<expression> args){
    return construct(
        functionIndex,
        TupleExpression::construct(std::forward<std::initializer_list<expression>>(args))
    );
}


expression FunctionExpression::simplify() {
    auto f = Functions::getSimplifyFunction(functionIndex);
    if (f){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg);
        return f(args);
    }
    return copy();
}
expression FunctionExpression::derivative(const std::string& var) {
    auto f = Functions::getDerivativeFunction(functionIndex);
    if (f){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg);
        return f(args, var);
    }
    throw Exception("Derivative not defined for: ", Functions::names[functionIndex]);
}
expression FunctionExpression::integrate(const std::string& var) {
    auto f = Functions::getIntegralFunction(functionIndex);
    if (f){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg);
        return f(args, var);
    }
    throw Exception("Integral not defined for: ", Functions::names[functionIndex]);
}

bool FunctionExpression::isComplex() const {
    return arg->isComplex();
}
bool FunctionExpression::isEvaluable(const Variables& vars) const {
    return arg->isEvaluable(vars);
}

expression FunctionExpression::eval(const Variables& vars) {
    auto evalFunction = Functions::getEvalFunction(functionIndex);
    if (evalFunction){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg->eval(vars));
        return evalFunction(args);
    }
    auto valueFunction = Functions::getValueFunction(functionIndex);
    if (valueFunction){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg->eval(vars));
        double x = args.nextValue();
        return NumExpression::construct(valueFunction(x));
    }
    throw Exception("Evaluation not defined for: ", Functions::names[functionIndex]);
}
double FunctionExpression::value(const Variables& vars) const {
    auto valueFunction = Functions::getValueFunction(functionIndex);
    if (valueFunction){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg->eval(vars));
        double x = args.nextValue();
        return valueFunction(x);
    }
    auto evalFunction = Functions::getEvalFunction(functionIndex);
    if (evalFunction){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg->eval(vars));
        return evalFunction(args)->value();
    }
    throw Exception("Value not defined for: ", Functions::names[functionIndex]);
}

bool FunctionExpression::equals(expression e, double precision) const {
    if (e == FUNCTION && functionIndex == e->id()){
        return arg->equals(e->at(0), precision);
    }
    return false;
}

expression FunctionExpression::at(const int index) {
    if (index == 0){
        return arg;
    }
    throw Exception("Array Index Out of Bounds (index: ", index, "): ", copy());
}

std::string FunctionExpression::repr() const {
    return Functions::names[functionIndex];
}
int FunctionExpression::id() const {
    return functionIndex;
}

std::ostream& FunctionExpression::print(std::ostream& out, const bool pretty) const {
    auto printFunction = Functions::getPrintFunction(functionIndex);
    if (printFunction){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg);
        return printFunction(out, args, pretty);
    }


    out << Functions::names[functionIndex];
    if (arg == TUPLE){
        return arg->print(out, pretty);
    }
    return arg->print(out << "(", pretty) << ")";
}
std::ostream& FunctionExpression::postfix(std::ostream& out) const {auto postfixFunction = Functions::getPostfixFunction(functionIndex);
    if (postfixFunction){
        auto signature = Functions::getSignature(functionIndex);
        auto args = signature.parse(arg);
        return postfixFunction(out, args);
    }


    arg->postfix(out) << " ";
    return out << Functions::names[functionIndex];
}
