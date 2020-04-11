
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Numerical Differentiation Evaluation Tests", "[deriv]" ) {

    SECTION("Test deriv Function"){
        requireIsEqual("deriv(sinx, 3)", -0.9899924966004454);
    }

}

TEST_CASE("Numerical Integration Evaluation Tests", "[integral]" ) {

    SECTION("Test integral Function"){
        requireIsEqual("integral(sincosx, 1, 4)", -1.397616561508279);
        requireIsEqual("integral(sincosx, 2, 4)", -1.4628367214483);
        requireIsEqual("integral(lnx, 0.5, 3)", 1.1424104562843017);
        requireIsEqual("integral(-sinx, 3, 5)", 1.273654682063672);
        requireIsEqual("integral(sqrt((1+x^2)/(1+x^4)), 0, 1)", 1.05335429864400326);
    }

}
