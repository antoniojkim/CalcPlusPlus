

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
    scannerTest("sin(3)", "sin ( 3 )");

    scannerTest("cos3", "cos 3");
    scannerTest("cos(3)", "cos ( 3 )");

    scannerTest("tan3", "tan 3");
    scannerTest("tan(3)", "tan ( 3 )");

    scannerTest("csc3", "csc 3");
    scannerTest("csc(3)", "csc ( 3 )");

    scannerTest("sec3", "sec 3");
    scannerTest("sec(3)", "sec ( 3 )");

    scannerTest("cot3", "cot 3");
    scannerTest("cot(3)", "cot ( 3 )");

    scannerTest("arcsinx", "arcsin x");
    scannerTest("arcsin(x)", "arcsin ( x )");

    scannerTest("arccosx", "arccos x");
    scannerTest("arccos(x)", "arccos ( x )");

    scannerTest("arctanx", "arctan x");
    scannerTest("arctan(x)", "arctan ( x )");

    scannerTest("arccscy", "arccsc y");
    scannerTest("arccsc(y)", "arccsc ( y )");

    scannerTest("arcsecy", "arcsec y");
    scannerTest("arcsec(y)", "arcsec ( y )");

    scannerTest("arccoty", "arccot y");

    scannerTest("logx", "log x");
    scannerTest("log2", "log2");

}

TEST_CASE("Complex Scanner Tests", "[scanner]" ) {

    scannerTest("sin(cos(3))", "sin ( cos ( 3 ) )");

    scannerTest("cossinh3+5i-arcsin(x, 4)+6integral(sinx, 4, 5)^|4+0x3aF",
                "cos sinh 3 + 5i - arcsin ( x , 4 ) + 6 integral ( sin x , 4 , 5 ) ^| 4 + 0x3aF");

}