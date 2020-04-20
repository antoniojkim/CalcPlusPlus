
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Basic Engine Evaluation Tests", "[test]" ) {

    SECTION("Test Single Binary Operations"){
        requireIsEqual("1 + 3", 4);
        requireIsEqual("7 - 30", -23);
        requireIsEqual("3.4 * 7.2", 24.48);
        requireIsEqual("5.7 ^ 5.9", 28817.8547768);
        requireIsEqual("5.7 ** 5.9", 28817.8547768);
    }

    SECTION("Test Compound Binary Operations for correct order"){
        requireIsEqual("5.7 - 2.4 * 5.9", -8.46);
        requireIsEqual("5.7 + 2.4 / 5.9", 6.106779661);
        requireIsEqual("5.7 + 2.4 // 5.9", 5.7);
        requireIsEqual("5.7 + 5.9 // 2.4", 7.7);
        requireIsEqual("5.7 + 5.9 % 2.4", 6.8);
    }

}

TEST_CASE("Basic Function Evaluation Tests", "[function]" ) {

    requireIsEqual("sin3", 0.141120008);

    SECTION("Test Full Bracket Expression"){
        requireIsEqual("sin(cos(3))", -0.83602186153773);
    }
    SECTION("Test Bracketless Expression"){
        requireIsEqual("sincos3", -0.83602186153773);
    }
}

TEST_CASE("Basic GSL Math Function Tests", "[basic_function]"){
    requireIsEqual("hypot(3, 4)", 5);
    requireIsEqual("hypot(3, 4, 5)", 7.071067811865475244);

    requireIsEqual("ldexp(.53, 7)", 67.84);
    requireIsEqual("frexp(67.84)", std::vector<double>{0.53, 7});

    requireIsEqual("fcmp(3, 3)", 1);
    requireIsEqual("fcmp(3, 3.1)", 0);
    requireIsEqual("fcmp(3, 3.000000000000001)", 1);
    requireIsEqual("fcmp(3, 3.0001, 1e-2)", 1);
    requireIsEqual("fcmp(3, 3.0001, 1E-2)", 1);
}
