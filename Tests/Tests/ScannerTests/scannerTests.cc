

#include <list>
#include <sstream>

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

void scannerTest(const string& input, const string& expected){
    auto tokens = engine.scan(input);
    REQUIRE( join(tokens, " ") == expected );
}

TEST_CASE("Basic Scanner Tests", "[scanner]" ) {

    scannerTest("sin3", "sin 3");
    scannerTest("cos(3)", "cos ( 3 )");
    scannerTest("tanx", "tan x");
    scannerTest("csc(x)", "csc ( x )");
    scannerTest("sec(cot(5))", "sec ( cot ( 5 ) )");
    scannerTest("sinhcosh5", "sinh cosh 5");
    scannerTest("log_25", "log_2 5");
    scannerTest("ln45", "ln 45");

}

TEST_CASE("Complex Scanner Tests", "[scanner]" ) {

    scannerTest("deriv(sinx, 3)",
                "deriv ( sin x , 3 )");

    scannerTest("cossinh3+5i-arcsin(x, 4)+6integral(sinx, 4, 5)^|4+0x3aF",
                "cos sinh 3 + 5i - arcsin ( x , 4 ) + 6 integral ( sin x , 4 , 5 ) ^| 4 + 0x3aF");

}