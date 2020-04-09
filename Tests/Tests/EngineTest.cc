#include "EngineTest.h"

#include <Catch2>
#include <iostream>
#include <sstream>
#include <gsl/gsl_math.h>

using namespace std;


MathEngine engine;


bool compare(double output, double expected){
    if (gsl_isnan(output) || gsl_isnan(expected)){
        return bool(gsl_isnan(output) && gsl_isnan(expected)) ? 0 : -1;
    }
    return gsl_fcmp(output, expected, 1e-8);
}


bool printDifference(const std::string& input, expression& expression, const double& output, const double& expected){
    cout << "Input:      " << input << endl;
    cout << "Expression: " << expression << endl;
    cout << "Postfix:    "; expression->postfix(cout) << endl;
#ifdef DEBUG
    cout << "Tokens:     "; print(cout, engine.tokens, " ") << endl;
#endif
    cout << output << " != " << expected << endl;
    cout << compare(output, expected) << endl;
    return false;
}

void requireIsEqual(const string& input, const double& expected){
    auto expression = engine.parse(input);
    double output = expression->value();
    REQUIRE( (compare(output, expected) != 0 ? printDifference(input, expression, output, expected) : true) ); 
}


bool printDifference(const std::string& input, expression& expression, const std::string& output, const std::string& expected){
    cout << "Input:      " << input << endl;
    cout << "Expression: " << expression << endl;
    cout << "Postfix:    "; expression->postfix(cout) << endl;
#ifdef DEBUG
    cout << "Tokens:     "; print(cout, engine.tokens, " ") << endl;
#endif
    cout << output << " != " << expected << endl;
    return false;
}

void requireIsEqual(const string& input, const std::string& expected){
    auto expression = engine.parse(input);
    ostringstream out;
    out << expression;
    string output = out.str();
    REQUIRE( ((output != expected) ? printDifference(input, expression, output, expected) : true) ); 
}
