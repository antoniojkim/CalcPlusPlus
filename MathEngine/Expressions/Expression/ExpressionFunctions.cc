
#include <utility>

#include "../ExpressionFunctions.h"
#include "../FunctionExpression.h"
#include "../NumericalExpression.h"

using namespace std;

expression abs(expression expr1){
    return FunctionExpression::construct("abs", expr1);
}
expression sqr(expression expr1){
    return FunctionExpression::construct("sqr", expr1);
}
expression sqrt(expression expr1){
    return FunctionExpression::construct("sqrt", expr1);
}
expression cb(expression expr1){
    return FunctionExpression::construct("cb", expr1);
}
expression cbrt(expression expr1){
    return FunctionExpression::construct("cbrt", expr1);
}
expression ln(expression expr1){
    return FunctionExpression::construct("ln", expr1);
}
