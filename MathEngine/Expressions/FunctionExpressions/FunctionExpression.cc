
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
        return InvalidExpression::construct(Exception("Invalid Function"));
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
    return Functions::getFunction(functionIndex)->simplify(arg);
}
expression FunctionExpression::derivative(const std::string& var) {
    return Functions::getFunction(functionIndex)->derivative(arg, var);
}
expression FunctionExpression::integrate(const std::string& var) {
    return Functions::getFunction(functionIndex)->integrate(arg, var);
}

bool FunctionExpression::isComplex() const {
    return arg->isComplex();
}
bool FunctionExpression::isEvaluable(const Variables& vars) const {
    return arg->isEvaluable(vars);
}

expression FunctionExpression::eval(const Variables& vars) {
    return Functions::getFunction(functionIndex)->eval(arg, vars);
}
double FunctionExpression::value(const Variables& vars) const {
    return Functions::getFunction(functionIndex)->value(arg, vars);
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
