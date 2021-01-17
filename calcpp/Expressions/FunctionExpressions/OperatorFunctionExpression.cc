
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Functions/Operators.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NullExpression.h"
#include "../NumericalExpression.h"


using namespace std;
using namespace Scanner;


OperatorFunctionExpression::OperatorFunctionExpression(int functionIndex, expression arg):
    FunctionExpression(functionIndex, arg, {{"lhs", Empty}, {"rhs", Empty}}) {} // Signature: (lhs, rhs)


std::ostream& OperatorFunctionExpression::print(std::ostream& out, const bool pretty) const {
    if(!Functions::isOperator(functionIndex)){
        return out << repr(); arg->print(out, pretty) << endl;
    }

    auto lhs = arg->at(0);
    auto rhs = arg->at(1);

    if (!pretty){
        out << "("; lhs->print(out, pretty) << ")";
        out << Functions::names[functionIndex];
        out << "("; rhs->print(out, pretty) << ")";
    }
    else{
        int precedence = Operators::getPrecedence(Operators::indexOf(repr()));
        if (lhs == FUNCTION && Functions::isOperator(lhs->id()) &&
            Operators::getPrecedence(Operators::indexOf(lhs->repr())) < precedence){
            out << "("; lhs->print(out, pretty) << ")";
        }
        else{
            lhs->print(out, pretty);
        }
        out << " " << repr() << " ";
        if (rhs == FUNCTION && Functions::isOperator(rhs->id()) &&
            Operators::getPrecedence(Operators::indexOf(rhs->repr())) < precedence){
            out << "("; rhs->print(out, pretty) << ")";
        }
        else{
            rhs->print(out, pretty);
        }
    }
    return out;
}
std::ostream& OperatorFunctionExpression::postfix(std::ostream& out) const {
    auto lhs = arg->at(0);
    auto rhs = arg->at(1);

    lhs->postfix(out) << " ";
    rhs->postfix(out) << " ";
    return out << repr();
}
