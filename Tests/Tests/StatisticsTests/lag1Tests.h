
#include "../EngineTest.h"

#include <Catch2>

#include <gsl/gsl_math.h>

TEST_CASE("Lag-1 Autocorrelate Function Evaluation Tests", "[lag1]") {
    
    SECTION("Empty Test"){
        requireIsEqual("lag1()", "Insufficient Number of Arguments for Function: lag1");
    }

    SECTION("`lag1` Test (all equal)"){
        requireIsEqual("lag1(1, 1, 1, 1)", GSL_NAN);
    }

    SECTION("`lag1` Test (some equal)"){
        requireIsEqual("autocorr(0, 1, 0, 1)", -0.75);
    }

    SECTION("`lag1` Test (some negatives)"){
        requireIsEqual("lag1(1, -1, 7, -4, 5)", -0.7797979797979797);
    }

    SECTION("`lag1` Test (some negatives and zero)"){
        requireIsEqual("autocorr(1, -3, 2, -5, 0)", -0.7647058823529411);
    }

    SECTION("`lag1` Test (positive, negative floats)"){
        requireIsEqual("lag1(1.0, -1.0, 2.0, -4.0, 5.0)", -0.6539823008849557);
    }

    SECTION("`lag1` Test (floats with zero)"){
        requireIsEqual("autocorr(1.1, -1.2, 2.3, -4.4, 0)", -0.6017621145374448);
    }

}

