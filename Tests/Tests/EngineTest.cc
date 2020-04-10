#include <iostream>
#include <sstream>

#include <Catch2>
#include <gsl/gsl_math.h>
#include <Expressions/TupleExpression.h>

#include "EngineTest.h"


using namespace std;


MathEngine engine;


int compare(double output, double expected){
    if (gsl_isnan(output) || gsl_isnan(expected)){
        return (gsl_isnan(output) && gsl_isnan(expected)) ? 0 : -1;
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

ostream& operator<<(ostream& out, const vector<double>& iterable){
    out << "(";
    for (auto& element : iterable){
        out << element << " ";
    }
    return out << ")";
}

bool printDifference(const std::string& input, expression& expr, expression& output, const std::vector<double>& expected){
    cout << "Input:      " << input << endl;
    cout << "Expression: " << expr << endl;
    cout << "Postfix:    "; expr->postfix(cout) << endl;
#ifdef DEBUG
    cout << "Tokens:     "; print(cout, engine.tokens, " ") << endl;
#endif
    cout << "Output:     "; output->print(cout) << endl;
    cout << "Expected:   " << expected << endl;
    return false;
}

bool compare(const list<expression>& l, const vector<double>& v) {
    if (l.size() != v.size()){
        return false;
    }
    if (l.size() == 0){
        return true;
    }
    auto b1 = l.begin();
    auto e1 = l.end();
    auto b2 = v.begin();
    auto e2 = v.end();
    while(b1 != e1 && b2 != e2){
        if (compare((*b1)->value(), *b2) != 0){
            return false;
        }
        ++b1;
        ++b2;
    }
    return true;
}

void requireIsEqual(const string& input, const std::vector<double>& expected){
    auto expr = engine.parse(input);
    auto output = expr->evaluate();
    auto tuple = dynamic_cast<TupleExpression*>(output.get());
    if (tuple){
        REQUIRE( (!compare(tuple->tuple, expected) ? printDifference(input, expr, output, expected) : true) ); 
    }
    else{
        printDifference(input, expr, output, expected);
        REQUIRE( false );
    }
}
