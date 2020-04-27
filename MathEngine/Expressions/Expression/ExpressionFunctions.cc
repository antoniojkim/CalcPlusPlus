
#include <utility>

#include "../ExpressionFunctions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"

using namespace std;

expression ln(expression&& expr1){
    return UnaryFunctionExpression::construct("ln", std::move(expr1));
}
