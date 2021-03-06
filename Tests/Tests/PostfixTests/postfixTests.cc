

#include <list>
#include <sstream>

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

void postfixTest(const string& input, const string& expected){
    auto expr = engine(input);
    ostringstream oss;
    expr->postfix(oss);
    auto output = oss.str();
    INFO("Input:    " << input);
    INFO("Expr:     " << expr);
    INFO("Postfix:  " << output);
    INFO("Expected: " << expected);
    CHECK( output == expected );
}

TEST_CASE("Basic Postfix Tests", "[postfix]" ) {

    postfixTest("sin3", "sin3");
    postfixTest("sin 3", "3 sin");
    postfixTest("cos(3)", "3 cos");
    postfixTest("tanx", "tanx");
    postfixTest("csc(x)", "x csc");
    postfixTest("sec(cot(5))", "5 cot sec");
    postfixTest("sinh(cosh 5)", "5 cosh sinh");
    postfixTest("log25", "log25");
    postfixTest("log_25", "log_25");
    postfixTest("log2(5)", "5 log2");
    postfixTest("ln 45", "45 ln");

}

TEST_CASE("Basic Operator Tests", "[postfix]" ) {

    postfixTest("3 + 4", "3 4 +");
    postfixTest("3 * 4", "3 4 *");

}

TEST_CASE("Multi Arg Function Postfix Tests", "[postfix]") {

    postfixTest("logn(10, 4)", "(10, 4) logn");
    postfixTest("deriv(sin(x), 3)", "(x sin, 3, x) deriv");
    postfixTest("mean(1, -1, 4+7, -4, 5)", "(1, -1, 4 7 +, -4, 5) mean");

}

TEST_CASE("Tuple Postfix Tests", "[postfix]") {

    postfixTest("(1, 2, 3, 4)", "(1, 2, 3, 4)");

}

TEST_CASE("Matrix Postfix Tests", "[postfix]") {

    postfixTest("{1, 2, 3, 4}", "{1, 2, 3, 4}");
    postfixTest("{{1, 2, 3}, {4, 5, 6}}", "{{1, 2, 3}, {4, 5, 6}}");
    postfixTest("{{1, 2}, {3, 4}, {5, 6}}", "{{1, 2}, {3, 4}, {5, 6}}");
    postfixTest("{{1, 2, 3, 4}}", "{1, 2, 3, 4}");
    postfixTest("det({{1, 2, 3, 4}})", "{1, 2, 3, 4} det");
    postfixTest("det{{1, 2, 3, 4}}", "{1, 2, 3, 4} det");
    postfixTest("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}}",
                "{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} {{1011, 1012}, {1021, 1022}, {1031, 1032}} *");

}

TEST_CASE("Complex Postfix Tests", "[postfix]" ) {

    postfixTest("cos(sinh3)+5i-arcsin(x)+6integral(sin(x), 4, 5)^|4+0x3aF",
                "sinh3 cos 5i + x arcsin - 6 (x sin, 4, 5, x) integral * + 4 0x3af + ^|");

    postfixTest("5 + x * 5 + mean ( 7 * 7 , 8 * ( 8 + x ) , 9 / 9 ) + { { sin ( 3 ) , - 2 } , { 3 ! , cos 4 } } + rand ( )",
                "5 x 5 * + (7 7 *, 8 8 x + *, 9 9 /) mean + {{3 sin, -2}, {3 fact, 4 cos}} + () rand +");

}
