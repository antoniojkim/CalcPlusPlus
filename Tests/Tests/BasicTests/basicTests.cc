

#include <cmath>
#include <iostream>
#include <string>

#include <Catch2>
#include <gsl/gsl_math.h>

#include "../EngineTest.h"

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

TEST_CASE("Basic Constants Tests", "[constants]"){
    requireIsEqual("pi", M_PI);
    requireIsEqual("π", M_PI);
    requireIsEqual("pi/2", M_PI_2);
    requireIsEqual("sqrt(pi)", M_SQRTPI);
    requireIsEqual("sqrtpi", M_SQRTPI);
    requireIsEqual("sqrtπ", M_SQRTPI);
    requireIsEqual("sqrte", sqrt(M_E));
    requireIsEqual("ϕ", 1.6180339887498948482);
    requireIsEqual("vphi", 1.6180339887498948482);
    requireIsEqual("γ", M_EULER);
    requireIsEqual("πe", M_PI * M_E);
    requireIsEqual("eπ", M_PI * M_E);
}

TEST_CASE("Basic Variable Setting Tests", "[constants]"){
    requireIsEqual("a=3", 3);
    requireIsEqual("3*a", 9);
    requireIsEqual("a:=4", 4);
    requireIsEqual("3*a", 12);
    requireIsEqual("a<-5", 5);
    requireIsEqual("3*a", 15);
    requireIsEqual("#a", "Deleted Variable: a", true);
}
