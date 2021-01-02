
#include <list>
#include <sstream>
#include <vector>

#include <Catch2>
#include "Scanner/scanner.h"

#include "../EngineTest.h"

using namespace std;
using namespace calcpp;

void scannerTest(const string& input, const vector<Token::Kind>& expected) {
    auto tokens = scan(input);
    CHECK(tokens.size() == expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        CHECK(tokens[i].kind == expected[i]);
    }
    // auto output = join(tokens, " ");
    // INFO("scan(" << input << ") == '" << output << "' != '" << expected << "'");
    // INFO("Tokens: ");
    // for (auto& token : tokens){
    //     INFO("    " << token.type << " " << typeStrings[token.type] << " '" <<
    //     token.lexeme << "'");
    // }
    // CHECK( output == expected );
}

TEST_CASE("Basic Number Scanner Tests", "[scanner]") {
    scannerTest("123", "123");
    scannerTest("0.5", "0.5");

    SECTION("Imaginary Numbers Test") {
        scannerTest("5i", "5i");
        scannerTest("5j", "5j");
    }

    SECTION("Exponential Notation Tests") {
        scannerTest("1e8", "1e8");
        scannerTest("1e-8", "1e-8");
        scannerTest("1e-8-", "1e-8 -");
        scannerTest("1-e8", "1 - e8");
        scannerTest("-1e8", "- 1e8");
    }

    SECTION("Constants Test") {
        scannerTest("πe", "π e");
        scannerTest("eπ", "e π");
    }
}

TEST_CASE("Basic Scanner Tests", "[scanner]") {
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

TEST_CASE("Complex Scanner Tests", "[scanner]") {
    scannerTest("deriv(sin(x), 3)", "deriv ( sin ( x ) , 3 )");

    scannerTest(
        "cos(sinh 3)+5i-arcsin(x, 4)+6integral(sin(x), 4, 5)^|4+0x3aF",
        "cos ( sinh 3 ) + 5i - arcsin ( x , 4 ) + 6 integral ( sin ( x ) , 4 , 5 ) ^| 4 "
        "+ 0x3aF");

    scannerTest(
        "5 + x * 5 + mean ( 7 * 7 , 8 * ( 8 + x ) , 9 / 9 ) + { { sin ( 3 ) , - 2 } , { "
        "3 ! , cos 4 } } + rand ( )",
        "5 + x * 5 + mean ( 7 * 7 , 8 * ( 8 + x ) , 9 / 9 ) + { { sin ( 3 ) , - 2 } , { "
        "3 ! , cos 4 } } + rand ( )");
}

TEST_CASE("Unit Conversion Scanner Tests", "[scanner]") {
    scannerTest("4km->m", "4 km -> m");
    scannerTest("5.7m/s -> km/h", "5.7 m / s -> km / h");
    scannerTest("5.7m/s^2 -> G", "5.7 m / s ^ 2 -> G");
}
