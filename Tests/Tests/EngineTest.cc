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
    ostringstream out;
    out << "Input:      " << input << endl;
    out << "Expression: " << expr << endl;
    out << "Postfix:    "; expr->postfix(out) << endl;
    out << output << " != " << expected << endl;
    out << "Compare:   " << compare(output, expected, 1e-8) << endl;
    UNSCOPED_INFO(out.str());
    return false;
}

bool printDifference(const std::string& input, const expression expr, const std::string& output, const std::string& expected){
    ostringstream out;
    out << "Input:      " << input << endl;
    out << "Expression: " << expr << endl;
    out << "Postfix:    "; expr->postfix(out) << endl;
    out << output << endl << " != " << endl << expected << endl;
    UNSCOPED_INFO(out.str());
    return false;
}

bool printDifference(const std::string& input, const expression expr, const expression output, const expression expectedExpr, const std::string& expected){
    ostringstream out;
    out << "Input:      " << input << endl;
    out << "Expression: " << expr << endl;
    out << "Postfix:    "; expr->postfix(out) << endl;
    out << "Expected:   "; expectedExpr->postfix(out) << endl;
    output->print(out, true) << endl << " != " << endl << expected << endl;
    UNSCOPED_INFO(out.str());
    return false;
}

void requireIsEqual(const string& input, const double expected){
    auto expression = engine.parse(input);
    double output = engine.eval(expression)->value();
    CHECK( (compare(output, expected, 1e-8) != 0 ? printDifference(input, expression, output, expected) : true) );
}

void requireIsEqual(const string& input, const std::string& expected, bool evaluate){
    auto expression = evaluate ? engine.eval(input) : engine.parse(input);
    ostringstream out;
    out << expression;
    string output = out.str();
    CHECK( ((output != expected) ? printDifference(input, expression, output, expected) : true) );
}

void requireExprIsEqual(const string& input, const std::string& expected){
    auto inputExpr = engine.parse(input)->simplify();
    auto outputExpr = engine.eval(inputExpr);
    auto expectedExpr = engine.parse(expected)->simplify();

    CHECK( ((!outputExpr->equals(expectedExpr, 1e-8)) ? printDifference(input, inputExpr, outputExpr, expectedExpr, expected) : true) );
}
