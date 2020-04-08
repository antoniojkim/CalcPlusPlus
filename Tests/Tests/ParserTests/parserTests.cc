
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Basic Parser Evaluation Tests", "[test]" ) {

    SECTION("Insufficient Number of Arguments for Unary Function"){
        requireIsEqual("sin", "Insufficient Number of Arguments for Function: sin");
    }

}
