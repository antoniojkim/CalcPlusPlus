#include <iostream>
#include <iomanip>
#include <sstream>

#include <Catch2>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <Expressions/TupleExpression.h>
#include <Expressions/MatrixExpression.h>
#include <Expressions/NumericalExpression.h>

#include "EngineTest.h"


using namespace std;


MathEngine engine;


int compare(double output, double expected){
    if (gsl_isnan(output) || gsl_isnan(expected)){
        return (gsl_isnan(output) && gsl_isnan(expected)) ? 0 : -1;
    }
    if (std::trunc(output) == output &&
        std::trunc(expected) == expected &&
        std::trunc(output) == std::trunc(expected)){
        return 0;
    }
    return gsl_fcmp(output, expected, 1e-8);
}

bool operator==(gsl_complex output, gsl_complex expected){
    int cmp = compare(GSL_REAL(output), GSL_REAL(expected));
    if (cmp == 0){
        return compare(GSL_IMAG(output), GSL_IMAG(expected)) == 0;
    }
    return false;
}

bool printDifference(const std::string& input, const expression expr, const double output, const double expected){
    cout << "Input:      " << input << endl;
    cout << "Expression: " << expr << endl;
    cout << "Postfix:    "; expr->postfix(cout) << endl;
#ifdef DEBUG
    cout << "Tokens:     "; print(cout, engine.tokens, " ") << endl;
#endif
    cout << output << " != " << expected << endl;
    cout << compare(output, expected) << endl;
    return false;
}

bool printDifference(const std::string& input, const expression expr, const std::string& output, const std::string& expected){
    cout << "Input:      " << input << endl;
    cout << "Expression: " << expr << endl;
    cout << "Postfix:    "; expr->postfix(cout) << endl;
#ifdef DEBUG
    cout << "Tokens:     "; print(cout, engine.tokens, " ") << endl;
#endif
    cout << output << " != " << expected << endl;
    return false;
}

bool printDifference(const std::string& input, const expression expr, const expression output, const std::string& expected){
    cout << "Input:      " << input << endl;
    cout << "Expression: " << expr << endl;
    cout << "Postfix:    "; expr->postfix(cout) << endl;
#ifdef DEBUG
    cout << "Tokens:     "; print(cout, engine.tokens, " ") << endl;
#endif
    cout << output << " != " << expected << endl;
    return false;
}

void requireIsEqual(const string& input, const double expected){
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

bool compare(expression output, expression expected){
    if (output->matrix() || expected->matrix()){
        if (output->matrix() && expected->matrix()){
            MatrixExpression* outputMatrix = output->matrix();
            MatrixExpression* expectedMatrix = expected->matrix();
            if (outputMatrix->rows() == expectedMatrix->rows() &&
                outputMatrix->cols() == expectedMatrix->cols()){
                auto outputIter = outputMatrix->getMatrix().begin();
                auto outputEnd = outputMatrix->getMatrix().end();
                auto expectedIter = expectedMatrix->getMatrix().begin();
                auto expectedEnd = expectedMatrix->getMatrix().end();
                while (outputIter != outputEnd && expectedIter != expectedEnd){
                    if (!compare(*outputIter, *expectedIter)){
                        return false;
                    }
                    ++outputIter;
                    ++expectedIter;
                }
                return true;
            }
        }
    }
    else if (output->tuple() || expected->tuple()){
        if (output->tuple() && expected->tuple()){
            TupleExpression* outputTuple = output->tuple();
            TupleExpression* expectedTuple = expected->tuple();
            if (outputTuple->data().size() == expectedTuple->data().size()){
                auto outputIter = outputTuple->data().begin();
                auto outputEnd = outputTuple->data().end();
                auto expectedIter = expectedTuple->data().begin();
                auto expectedEnd = expectedTuple->data().end();
                while (outputIter != outputEnd && expectedIter != expectedEnd){
                    if (!compare(*outputIter, *expectedIter)){
                        return false;
                    }
                    ++outputIter;
                    ++expectedIter;
                }
                return true;
            }
        }
    }
    else if (output->evaluable() && expected->evaluable()){
        return output->complex() == expected->complex();
    }
    return false;
}

void requireExprIsEqual(const string& input, const std::string& expected){
    auto inputExpr = engine.parse(input);
    auto outputExpr = inputExpr->evaluate();
    auto expectedExpr = engine.parse(expected)->simplify();

    REQUIRE( (!compare(outputExpr, expectedExpr) ? printDifference(input, inputExpr, outputExpr, expected) : true) );
}
