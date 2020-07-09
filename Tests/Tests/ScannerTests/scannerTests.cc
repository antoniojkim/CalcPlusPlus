

#include <list>
#include <sstream>

#include <Catch2>
#include "Scanner/scanner.h"

#include "../EngineTest.h"

using namespace std;
using namespace Scanner;

void scannerTest(const string& input, const string& expected){
    auto tokens = engine.scan(input);
    auto output = join(tokens, " ");
    if (output != expected){
        UNSCOPED_INFO("scan(" << input << ") == '" << output << "' != '" << expected << "'");
        UNSCOPED_INFO("Tokens: ");
        for (auto& token : tokens){
            UNSCOPED_INFO("    " << token.type << " " << typeStrings[token.type] << " '" << token.lexeme << "'");
        }
    }
    CHECK( output == expected );
}

TEST_CASE("Basic Number Scanner Tests", "[scanner]" ) {

    scannerTest("123", "123");
    scannerTest("0.5", "0.5");

    SECTION("Imaginary Numbers Test"){
        scannerTest("5i", "5i");
        scannerTest("5j", "5j");
    }

    SECTION("Exponential Notation Tests"){
        scannerTest("1e8", "1e8");
        scannerTest("1e-8", "1e-8");
        scannerTest("1e-8-", "1e-8 -");
        scannerTest("1-e8", "1 - e8");
        scannerTest("-1e8", "- 1e8");
    }

    SECTION("Constants Test"){
        scannerTest("πe", "π e");
        scannerTest("eπ", "e π");
    }

}


TEST_CASE("Basic Scanner Tests", "[scanner]" ) {

    scannerTest("sin3", "sin3");
    scannerTest("sin 3", "sin 3");
    scannerTest("cos(3)", "cos ( 3 )");
    scannerTest("tanx", "tanx");
    scannerTest("csc(x)", "csc ( x )");
    scannerTest("sec(cot(5))", "sec ( cot ( 5 ) )");
    scannerTest("sinh(cosh 5)", "sinh ( cosh 5 )");
    scannerTest("log_25", "log_25");
    scannerTest("ln45", "ln45");

}

TEST_CASE("Complex Scanner Tests", "[scanner]" ) {

    scannerTest("deriv(sin(x), 3)",
                "deriv ( sin ( x ) , 3 )");

    scannerTest("cos(sinh 3)+5i-arcsin(x, 4)+6integral(sin(x), 4, 5)^|4+0x3aF",
                "cos ( sinh 3 ) + 5i - arcsin ( x , 4 ) + 6 integral ( sin ( x ) , 4 , 5 ) ^| 4 + 0x3aF");

}

TEST_CASE("Unit Conversion Scanner Tests", "[scanner]" ) {

    scannerTest("4km->m", "4 km -> m");
    scannerTest("5.7m/s -> km/h", "5.7 m / s -> km / h");
    scannerTest("5.7m/s^2 -> G", "5.7 m / s ^ 2 -> G");

}
