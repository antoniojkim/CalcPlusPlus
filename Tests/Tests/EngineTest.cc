#include <iostream>
#include <iomanip>
#include <sstream>

#include <Catch2>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <Expressions/TupleExpression.h>
#include <Expressions/MatrixExpression.h>
#include <Expressions/NumericalExpression.h>
#include <Utils/Numeric.h>

#include "EngineTest.h"


using namespace std;


MathEngine engine;


bool printDifference(const std::string& input, const expression expr, const double output, const double expected){
    UNSCOPED_INFO("Input:      " << input);
    UNSCOPED_INFO("Expression: " << expr);
    ostringstream postfix;
    expr->postfix(postfix);
    UNSCOPED_INFO("Postfix:    " << postfix.str());
    UNSCOPED_INFO(output << " != " << expected);
    UNSCOPED_INFO(compare(output, expected));
    return false;
}

bool printDifference(const std::string& input, const expression expr, const std::string& output, const std::string& expected){
    UNSCOPED_INFO("Input:      " << input);
    UNSCOPED_INFO("Expression: " << expr);
    ostringstream postfix;
    expr->postfix(postfix);
    UNSCOPED_INFO("Postfix:    " << postfix.str());
    UNSCOPED_INFO(output);
    UNSCOPED_INFO(" != ");
    UNSCOPED_INFO(expected);
    return false;
}

bool printDifference(const std::string& input, const expression expr, const expression output, const expression expectedExpr, const std::string& expected){
    UNSCOPED_INFO("Input:      " << input);
    UNSCOPED_INFO("Expression: " << expr);
    ostringstream postfix;
    postfix << "Postfix:    "; expr->postfix(postfix) << endl;
    postfix << "Expected:    "; expectedExpr->postfix(postfix);
    UNSCOPED_INFO(postfix.str());
    UNSCOPED_INFO(output);
    UNSCOPED_INFO(" != ");
    UNSCOPED_INFO(expected);
    return false;
}

void requireIsEqual(const string& input, const double expected){
    auto expression = engine.parse(input);
    double output = expression->value();
    CHECK( (compare(output, expected, 1e-8) != 0 ? printDifference(input, expression, output, expected) : true) );
}

void requireIsEqual(const string& input, const std::string& expected, bool evaluate){
    auto expression = evaluate ? engine.evaluate(input) : engine.parse(input);
    ostringstream out;
    out << expression;
    string output = out.str();
    CHECK( ((output != expected) ? printDifference(input, expression, output, expected) : true) );
}

void requireExprIsEqual(const string& input, const std::string& expected){
    auto inputExpr = engine.parse(input);
    auto outputExpr = inputExpr->eval();
    auto expectedExpr = engine.parse(expected)->simplify();

    CHECK( ((!outputExpr->equals(expectedExpr, 1e-8)) ? printDifference(input, inputExpr, outputExpr, expectedExpr, expected) : true) );
}
