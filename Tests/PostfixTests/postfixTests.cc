

#include <list>
#include <sstream>

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

void postfixTest(const string& input, const string& expected){
    auto expr = engine(input);
    ostringstream oss;
    expr->postfix(oss);
    REQUIRE( oss.str() == expected );
}

TEST_CASE("Basic Postfix Tests", "[postfix]" ) {

    postfixTest("sin3", "3 sin");
    postfixTest("cos(3)", "3 cos");
    postfixTest("tanx", "x tan");
    postfixTest("csc(x)", "x csc");
    postfixTest("sec(cot(5))", "5 cot sec");
    postfixTest("sinhcosh5", "5 cosh sinh");
    postfixTest("log25", "5 log2");
    postfixTest("ln45", "45 ln");

}

TEST_CASE("Multi Arg Function Postfix Tests", "[postfix]") {

    postfixTest("logn(10, 4)", "10 4 , logn");

}

TEST_CASE("Complex Postfix Tests", "[postfix]" ) {

    // postfixTest("cossinh3+5i-arcsin(x, 4)+6integral(sinx, 4, 5)^|4+0x3aF",
    //             "3 sinh cos 5i + arcsin ( x , 4 ) - 6 integral ( sin x , 4 , 5 )  4 ^| 0x3aF + +");

}