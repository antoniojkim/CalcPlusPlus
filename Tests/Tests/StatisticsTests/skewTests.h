
#include "../EngineTest.h"

#include <Catch2>

#include <gsl/gsl_math.h>

TEST_CASE("Skew Function Evaluation Tests", "[skew]") {
    
    SECTION("Empty Test"){
        requireIsEqual("skew()", "Insufficient Number of Arguments for Function: skew");
    }

    SECTION("`skew` Test (all equal)"){
        requireIsEqual("skew(1, 1, 1, 1)", GSL_NAN);
    }

    SECTION("`skew` Test (some equal)"){
        requireIsEqual("skew(0, 1, 0, 1)", 0);
    }

    SECTION("`skew` Test (some negatives)"){
        requireIsEqual("skew(1, -1, 7, -4, 5)", 0.007627311575341911);
    }

    SECTION("`skew` Test (some negatives and zero)"){
        requireIsEqual("skew(1, -3, 2, -5, 0)", -0.2905387795355443);
    }

    SECTION("`skew` Test (positive, negative floats)"){
        requireIsEqual("skew(1.0, -1.0, 2.0, -4.0, 5.0)", -0.07076387377548059);
    }

    SECTION("`skew` Test (floats with zero)"){
        requireIsEqual("skew(1.1, -1.2, 2.3, -4.4, 0)", -0.4526856142746512);
    }

}

