

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

    requireIsEqual("sin(3)", 0.141120008);
    requireIsEqual("sin 3", 0.141120008);

    SECTION("Test Full Bracket Expression"){
        requireIsEqual("sin(cos(3))", -0.83602186153773);
    }
    SECTION("Test Bracketless Expression"){
        requireIsEqual("sin cos 3", -0.83602186153773);
    }
}

TEST_CASE("Basic GSL Math Function Tests", "[basic_function]"){
    requireIsEqual("hypot(3, 4)", 5);
    requireIsEqual("hypot(3, 4, 5)", 7.071067811865475244);
    requireIsEqual("hypot(3, 4, 5, 6)", 9.273618495495704);

    requireIsEqual("ldexp(.53, 7)", 67.84);
    requireExprIsEqual("frexp(67.84)", "(0.53, 7)");

    requireIsEqual("fcmp(3, 3)", 0);
    requireIsEqual("fcmp(3, 3.1)", -1);
    requireIsEqual("fcmp(3, 3.000000000000001)", 0);
    requireIsEqual("fcmp(3, 3.0001, 1e-2)", 0);
    requireIsEqual("fcmp(3, 3.0001, 1E-2)", 0);
}

TEST_CASE("Basic Constants Tests", "[constants]"){
    requireIsEqual("pi", M_PI);
    requireIsEqual("π", M_PI);
    requireIsEqual("pi/2", M_PI_2);
    requireIsEqual("sqrt(pi)", M_SQRTPI);
    requireIsEqual("sqrt pi", M_SQRTPI);
    requireIsEqual("sqrt π", M_SQRTPI);
    requireIsEqual("sqrt e", sqrt(M_E));
    requireIsEqual("ϕ", 1.6180339887498948482);
    requireIsEqual("vphi", 1.6180339887498948482);
    requireIsEqual("γ", M_EULER);
    requireIsEqual("πe", M_PI * M_E);
    requireIsEqual("e * π", M_E * M_PI);
}

TEST_CASE("Basic Variable Setting Tests", "[variables]"){
    requireIsEqual("a=3", 3);
    requireIsEqual("3*a", 9);
    requireIsEqual("a:=4", 4);
    requireIsEqual("3*a", 12);
    requireIsEqual("a<-3*2", 6);
    requireIsEqual("3*a", 18);
    requireIsEqual("a=None", "Deleted Variable: a", true);
    requireIsEqual("3*a", GSL_NAN);
}

TEST_CASE("Hex and Bin Conversion Tests", "[hexbin]"){
    SECTION("Hex Conversion Tests"){
        requireIsEqual("hex(345)", "0x159", true);
        requireIsEqual("0x7b * 0x1c8", "0xdb18", true);
        requireIsEqual("hex(123) * hex(456)", "0xdb18", true);
        requireIsEqual("hex(123 * 456)", "0xdb18", true);
    }

    SECTION("Bin Conversion Tests"){
        requireIsEqual("bin(345)", "0b101011001", true);
        requireIsEqual("bin(123 * 456)", "0b1101101100011000", true);
        requireIsEqual("bin(123) * bin(456)", "0b1101101100011000", true);
        requireIsEqual("0b1111011 * 0b111001000", "0b1101101100011000", true);
    }

    requireIsEqual("hex(123) * 0b111001000", "0xdb18", true);
    requireIsEqual("num(hex(123) * 0b111001000)", 56088);
}

TEST_CASE("GCD/LCM Conversion Tests", "[gcdlcm]"){
    SECTION("gcd Tests"){
        requireIsEqual("gcd(345, 456)", 3);
        requireIsEqual("gcd(11, 4574764567)", 1);
        requireIsEqual("gcd(346, -6)", 2);
    }
    SECTION("lcm Tests"){
        requireIsEqual("lcm(23, 67)", 1541);
        requireIsEqual("lcm(12, 16)", 48);
        requireIsEqual("lcm(346, -6)", 1038);
    }
}
