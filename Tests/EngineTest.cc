#include "EngineTest.h"

#include <Catch2>
#include <iostream>
#include <sstream>
#include <gsl/gsl_math.h>

using namespace std;

MathEngine engine;

bool printDifference(expression& expression, const double& output, const double& expected){
    cout << expression << endl;
    cout << output << " != " << expected << endl;
    cout << gsl_fcmp(output, expected, 1e-6) << endl;
    return false;
}

void requireIsEqual(const string& input, const double& expected){
    auto expression = engine.eval(input);
    double output = expression->value();
    REQUIRE( (gsl_fcmp(output, expected, 1e-6) != 0 ? printDifference(expression, output, expected) : true) ); 
}

bool printDifference(expression& expression, const std::string& output, const std::string& expected){
    cout << expression << endl;
    cout << output << " != " << expected << endl;
    return false;
}

void requireIsEqual(const string& input, const std::string& expected){
    auto expression = engine.eval(input);
    ostringstream out;
    out << expression;
    string output = out.str();
    REQUIRE( ((output != expected) ? printDifference(expression, output, expected) : true) ); 
}
