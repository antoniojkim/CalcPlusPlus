

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
    if (output != expected){
        cout << "Input:   " << input << endl;
        cout << "Postfix: " << output << endl;
#ifdef DEBUG
        cout << "Postfix Tokens: "; print(cout, engine.tokens, " ") << endl;
#endif
    }
    REQUIRE( output == expected );
}

TEST_CASE("Basic Postfix Tests", "[postfix]" ) {

    postfixTest("sin3", "3 sin");
    postfixTest("cos(3)", "3 cos");
    postfixTest("tanx", "x tan");
    postfixTest("csc(x)", "x csc");
    postfixTest("sec(cot(5))", "5 cot sec");
    postfixTest("sinhcosh5", "5 cosh sinh");
    postfixTest("log25", "25 log");
    postfixTest("log_25", "5 log_2");
    postfixTest("ln45", "45 ln");

}

TEST_CASE("Multi Arg Function Postfix Tests", "[postfix]") {

    postfixTest("logn(10, 4)", "10 4 , logn");
    postfixTest("deriv(sinx, 3)", "x sin 3 , deriv");
    postfixTest("mean(1, -1, 7, -4, 5)", "1 -1 7 -4 5 , , , , mean");

}

TEST_CASE("Complex Postfix Tests", "[postfix]" ) {

    // postfixTest("cossinh3+5i-arcsin(x, 4)+6integral(sinx, 4, 5)^|4+0x3aF",
    //             "3 sinh cos 5i + arcsin ( x , 4 ) - 6 integral ( sin x , 4 , 5 )  4 ^| 0x3aF + +");

}