#include <iostream>
#include <iomanip>
#include <sstream>

#include <Catch2>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <Expressions/TupleExpression.h>
#include <Expressions/MatrixExpression.h>

#include "EngineTest.h"


using namespace std;


MathEngine engine;


int compare(double output, double expected){
    if (gsl_isnan(output) || gsl_isnan(expected)){
        return (gsl_isnan(output) && gsl_isnan(expected)) ? 0 : -1;
    }
    return gsl_fcmp(output, expected, 1e-8);
}

int compare(gsl_complex output, gsl_complex expected){
    int cmp = compare(GSL_REAL(output), GSL_REAL(expected));
    if (cmp == 0){
        return compare(GSL_IMAG(output), GSL_IMAG(expected));
    }
    return cmp;
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

bool compare(const list<expression>& l, const vector<gsl_complex>& v) {
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
        if (compare((*b1)->complex(), *b2) != 0){
            return false;
        }
        ++b1;
        ++b2;
    }
    return true;
}

bool compare(gsl_matrix* m, const vector<vector<double>>& v) {
    if (m->size1 != v.size() || m->size2 != v.begin()->size()){
        return false;
    }
    size_t i = 0, j = 0;
    for (auto& iter : v){
        j = 0;
        for (auto& element : iter){
            if (compare(gsl_matrix_get(m, i, j), element) != 0){
                return false;
            }
            ++j;
        }
        ++i;
    }
    return true;
}

bool compare(gsl_matrix_complex* m, const vector<vector<gsl_complex>>& v) {
    if (m->size1 != v.size() || m->size2 != v.begin()->size()){
        return false;
    }
    size_t i = 0, j = 0;
    for (auto& iter : v){
        j = 0;
        for (auto& element : iter){
            if (compare(gsl_matrix_complex_get(m, i, j), element) != 0){
                return false;
            }
            ++j;
        }
        ++i;
    }
    return true;
}

ostream& operator<<(ostream& out, const gsl_complex& val){
    if (GSL_REAL(val) != 0){
        out << std::setprecision(16) << GSL_REAL(val);
        if (GSL_IMAG(val) > 0){ out << "+"; }
    }
    if (GSL_IMAG(val) != 0){
        out << std::setprecision(16) << GSL_IMAG(val) << "i";
    }
    return out;
}
ostream& operator<<(ostream& out, const vector<double>& iterable){
    out << "(";
    for (auto& element : iterable){
        out << element << " ";
    }
    return out << ")";
}
ostream& operator<<(ostream& out, const vector<gsl_complex>& iterable){
    out << "(";
    for (auto& element : iterable){
        out << GSL_REAL(element);
        if (GSL_IMAG(element) < 0){
            out << GSL_IMAG(element) << "i" << " ";
        }
        else{
            out << "+" << GSL_IMAG(element) << "i" << " ";
        }
    }
    return out << ")";
}
ostream& operator<<(ostream& out, const vector<vector<double>>& iterable){
    out << "{";
    for(auto& iter : iterable){
        out << "{";
        for (auto& element : iter){
            out << element << " ";
        }
        out << "}";
    }
    return out << "}";
}
ostream& operator<<(ostream& out, const vector<vector<gsl_complex>>& iterable){
    out << "{";
    for(auto& iter : iterable){
        out << "{";
        for (auto& element : iter){
            out << GSL_REAL(element);
            if (GSL_IMAG(element) < 0){
                out << GSL_IMAG(element) << "i" << " ";
            }
            else{
                out << "+" << GSL_IMAG(element) << "i" << " ";
            }
        }
        out << "}";
    }
    return out << "}";
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

bool printDifference(const std::string& input, expression& expression, const gsl_complex& output, const gsl_complex& expected){
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

bool printDifference(const std::string& input, expression& expr, expression& output, const std::vector<gsl_complex>& expected){
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

bool printDifference(const std::string& input, expression& expr, expression& output, const std::vector<std::vector<double>>& expected){
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

bool printDifference(const std::string& input, expression& expr, expression& output, const std::vector<std::vector<gsl_complex>>& expected){
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


void requireIsEqual(const string& input, const double& expected){
    auto expression = engine.evaluate(input);
    double output = expression->value();
    REQUIRE( (compare(output, expected) != 0 ? printDifference(input, expression, output, expected) : true) );
}

void requireIsEqual(const string& input, const std::string& expected, bool evaluate){
    auto expression = evaluate ? engine.evaluate(input) : engine.parse(input);
    ostringstream out;
    out << expression;
    string output = out.str();
    REQUIRE( ((output != expected) ? printDifference(input, expression, output, expected) : true) );
}

void requireIsEqual(const string& input, const gsl_complex& expected){
    auto expression = engine.evaluate(input);
    auto output = expression->complex();
    REQUIRE( (compare(output, expected) != 0 ? printDifference(input, expression, output, expected) : true) );
}

void requireIsEqual(const string& input, const std::vector<double>& expected){
    auto expr = engine.parse(input);
    auto output = expr->evaluate();
    auto tuple = output->tuple();
    if (tuple){
        REQUIRE( (!compare(tuple->data(), expected) ? printDifference(input, expr, output, expected) : true) );
    }
    else{
        printDifference(input, expr, output, expected);
        REQUIRE( false );
    }
}

void requireIsEqual(const string& input, const std::vector<gsl_complex>& expected){
    auto expr = engine.parse(input);
    auto output = expr->evaluate();
    auto tuple = output->tuple();
    if (tuple){
        REQUIRE( (!compare(tuple->data(), expected) ? printDifference(input, expr, output, expected) : true) );
    }
    else{
        printDifference(input, expr, output, expected);
        REQUIRE( false );
    }
}

void requireIsEqual(const string& input, const std::vector<std::vector<double>>& expected){
    auto expr = engine.parse(input);
    auto output = expr->evaluate();
    auto matrix = output->matrix();
    if (matrix){
        REQUIRE( (!compare(matrix->to_gsl_matrix().get(), expected) ? printDifference(input, expr, output, expected) : true) );
    }
    else{
        printDifference(input, expr, output, expected);
        REQUIRE( false );
    }
}

void requireIsEqual(const string& input, const std::vector<std::vector<gsl_complex>>& expected){
    auto expr = engine.parse(input);
    auto output = expr->evaluate();
    auto matrix = output->matrix();
    if (matrix){
        REQUIRE( (!compare(matrix->to_gsl_matrix_complex().get(), expected) ? printDifference(input, expr, output, expected) : true) );
    }
    else{
        printDifference(input, expr, output, expected);
        REQUIRE( false );
    }
}
