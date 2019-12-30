

#include <iostream>
#include <list>
#include <sstream>

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

/*
    Check to see if any errors arise from parsing the input
*/
void parserTest(const string& input){
    auto tree = engine.parse(input);
    REQUIRE( input == input );
}

TEST_CASE("Basic Parser Tests", "[parser]" ) {

    SECTION("Test Bracketless Parsing"){
        parserTest("sincos3");
        parserTest("sinhcosx");
        parserTest("sinxcosy");
    }

    SECTION("Test Inner Bracket Parsing"){
        parserTest("sincos(3)");
    }
    SECTION("Test Outer Bracket Parsing"){
        parserTest("sin(cos3)");
    }
    SECTION("Test Full Bracket Parsing"){
        parserTest("sin(cos(3))");
    }

}

TEST_CASE("Complex Parser Tests", "[Parser]" ) {

    // parserTest("cossinh3+5i-arcsin(x, 4)*6integral(sinx, 4, 5)^|4/0x3aF");

}