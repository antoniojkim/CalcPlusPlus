
#include <string>

#include "../NumericalExpression.h"
#include "../VariableExpression.h"

using namespace std;

expression NumericalExpression::derivative(const std::string& var) override {
    return NumExpression::construct(0);
}
expression NumericalExpression::integrate(const std::string& var) override {
    return copy() * VariableExpression::construct(var);
}
