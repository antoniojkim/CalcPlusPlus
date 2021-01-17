
#include <memory>
#include <utility>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../FunctionExpression.h"
#include "../NullExpression.h"
#include "../NumericalExpression.h"

using namespace std;
using namespace Scanner;


ValueFunctionExpression::ValueFunctionExpression(int functionIndex, ValueFunction f, expression arg):
    FunctionExpression(functionIndex, arg, {{"x", Empty}}), f{f} {} // Signature: (x)


expression ValueFunctionExpression::construct(int functionIndex, ValueFunction f, const expression arg){
    return shared_ptr<ValueFunctionExpression>(new ValueFunctionExpression(functionIndex, f, arg));
}


double ValueFunctionExpression::value(const Variables& vars) const {
    double x = arg->at(0)->value(vars);
    return f(x);
}
