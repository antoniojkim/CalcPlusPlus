
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Numerical Differentiation Evaluation Tests", "[deriv]" ) {

    SECTION("Test deriv Function"){
        requireIsEqual("deriv(sinx, 3)", -0.9899924966004454);
        requireIsEqual("deriv(ln(x^2 + ln(x*2 + x^3) + sin(cos(x))), 10)", 0.194564706303018368455);
    }
    SECTION("Test diff Function"){
        requireIsEqual("diff(sinx)", "cos(x)", true);
        requireIsEqual("diff(ln(x^2 + ln(x*2 + x^3) + sin(cos(x))))", "1 / (x ^ 2 + ln(x * 2 + x ^ 3) + sin(cos(x))) * (2 * x + 1 / (x * 2 + x ^ 3) * (3 * sqr(x) + 2) + cos(cos(x)) * neg(sin(x)))", true);
    }

}

TEST_CASE("Numerical Integration Evaluation Tests", "[integral]" ) {

    SECTION("Test integral Function"){
        requireIsEqual("integral(sincosx, 1, 4)", -1.397616561508279);
        requireIsEqual("integral(sincosx, 2, 4)", -1.4628367214483);
        requireIsEqual("integral(lnx, 0.5, 3)", 1.1424104562843017);
        requireIsEqual("integral(-sinx, 3, 5)", 1.273654682063672);
        requireIsEqual("integral(sqrt((1+x^2)/(1+x^4)), 0, 1)", 1.05335429864400326);
        requireIsEqual("integral(sqrt(2*x), 1, 30)", 153.976524806714612);
    }

}
