

#include <list>
#include <sstream>

using namespace std;

#include <Catch2>
#include "scannerTests.h"
#include "../../MathEngine/MathEngine.h"

MathEngine engine;

void scannerTest(const string& input, const string& expected){
    auto tokens = engine.scan(input);
    REQUIRE( join(tokens, " ") == expected );
}

TEST_CASE("Scanner Tests", "[scanner]" ) {

    SECTION("Basic Tests"){
        scannerTest("atanh3", "atanh 3");
        scannerTest("atanh(3)", "atanh ( 3 )");
    }

    SECTION("Complex Tests"){
        scannerTest("cossinh3+5i-arcsin(x, 4)+6integral(sinx, 4, 5)^|4+0x3aF",
                    "cos sinh 3 + 5i - arcsin ( x , 4 ) + 6 integral ( sin x , 4 , 5 ) ^| 4 + 0x3aF");
    }

}