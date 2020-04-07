
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Exp/Log Function Evaluation Tests", "[expLog]" ) {

    SECTION("Test Log Functions"){
        requireIsEqual("ln3", 1.0986122886681);
        requireIsEqual("ln(3)", 1.0986122886681);
        requireIsEqual("ln24", 2);  // Parsing algorithm assumes ln2(4) or log 4 base 2.
        requireIsEqual("ln2(4)", 2);
    }

    SECTION("Test Exp Functions"){
        requireIsEqual("exp2", 7.38905609893065);
        requireIsEqual("expm12", 6.38905609893065);  // Parsing algorithm assumes expm1(2)
    }

    SECTION("Test Multi Argument Log Functions"){
        requireIsEqual("logn(10, 4)", 1.66096404744368);
    }

}
