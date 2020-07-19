
#include <iomanip>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../NullExpression.h"
#include "../NumericalExpression.h"
#include "../UnitExpression.h"
#include "../TupleExpression.h"
#include "../VariableExpression.h"
#include "Constants.h"

using namespace std;
using namespace Scanner;

VarArgsExpression::VarArgsExpression(): Expression{VARARGS}{}
VarArgsExpression::VarArgsExpression(expression var): Expression{VARARGS}, var{var} {}

expression VarArgsExpression::construct(){
    return shared_ptr<VarArgsExpression>(new VarArgsExpression());
}

expression VarArgsExpression::construct(expression var){
    if (var != VAR && var != EMPTY){
        throw Exception("VarArgs Expression expected a variable. Got: ", var);
    }
    return shared_ptr<VarArgsExpression>(new VarArgsExpression(var));
}

extern expression EmptyVarArgs = VarArgsExpression::construct(Empty);

bool VarArgsExpression::isComplex() const { return var->isComplex(); }
bool VarArgsExpression::isEvaluable(const Variables& vars) const {
    return var->isEvaluable(vars);
}

expression VarArgsExpression::eval(const Variables& vars) { return var->eval(vars); }
double VarArgsExpression::value(const Variables& vars) const { return var->value(vars); }

bool VarArgsExpression::equals(expression e, double precision) const {
    if (e == VARARGS){
        return var->equals(e->at(0), precision);
    }
    return false;
}

expression VarArgsExpression::at(const int index) {
    switch(index){
        case 0: return copy();
        case 1: return var;
        default: throw Exception("VarArgsExpression::at: Index out of bounds: ", index);
    }
}

std::ostream& VarArgsExpression::print(std::ostream& out, const bool pretty) const {
    return var->print(out, pretty) << "...";
}
std::ostream& VarArgsExpression::postfix(std::ostream& out) const {
    return var->postfix(out) << " ...";
}
