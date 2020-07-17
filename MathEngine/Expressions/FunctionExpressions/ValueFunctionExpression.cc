
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"

using namespace std;
using namespace Scanner;


ValueFunctionExpression::ValueFunctionExpression(int functionIndex, ValueFunction f, expression arg):
    FunctionExpression(functionIndex, arg, 1), f{f} {}

ValueFunctionExpression::ValueFunctionExpression(int functionIndex, ValueFunction f, expression arg):
    FunctionExpression(functionIndex, arg, 1), f{f} {}


expression ValueFunctionExpression::construct(int functionIndex, ValueFunction f, const expression arg){
    return shared_ptr<ValueFunctionExpression>(new ValueFunctionExpression(functionIndex, f, arg));
}


double ValueFunctionExpression::value(const Variables& vars) const {
    double x = arg->value(vars);
    return f(x);
}
