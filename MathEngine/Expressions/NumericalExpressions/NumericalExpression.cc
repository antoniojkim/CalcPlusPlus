
#include <string>

#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"
#include "../VariableExpression.h"

using namespace std;
using namespace Scanner;

NumericalExpression::NumericalExpression(Scanner::Type kind): Expression(kind) {}

expression NumericalExpression::derivative(const std::string& var) {
    return NumExpression::construct(0);
}
expression NumericalExpression::integrate(const std::string& var) {
    return copy() * VariableExpression::construct(var);
}
