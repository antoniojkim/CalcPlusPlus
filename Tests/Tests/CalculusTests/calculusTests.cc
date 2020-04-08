
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Calculus Function Evaluation Tests", "[calculus]" ) {

    SECTION("Test deriv Function"){
        cout << "deriv(sinx, 3) == " <<
        engine.parse("deriv(sinx, 3)")->value() << endl;
        requireIsEqual("deriv(sinx, 3)", -0.9899924966004454);
    }

}
