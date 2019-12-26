

#include <iostream>
#include <list>
#include <sstream>

using namespace std;

#include <Catch2>
#include "../EngineTest.h"
#include "parserTests.h"

void parserTest(const string& input, const string& expected){
    auto tree = engine.parse(input);
    tree->print(cout);
    ostringstream out;
    tree->print(out);

    REQUIRE( out.str() == expected );
}

TEST_CASE("Basic Parser Tests", "[parser]" ) {

    parserTest("sincos3", "sin cos 3");

}