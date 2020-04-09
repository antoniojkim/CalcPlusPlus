
#include "../EngineTest.h"

#include <Catch2>

#include <gsl/gsl_math.h>

TEST_CASE("kurtosis Function Evaluation Tests", "[kurtosis]") {
    
    SECTION("Empty Test"){
        requireIsEqual("kurtosis()", "Insufficient Number of Arguments for Function: kurtosis");
    }

    SECTION("`kurtosis` Test (all equal)"){
        requireIsEqual("kurtosis(1, 1, 1, 1)", GSL_NAN);
    }

    SECTION("`kurtosis` Test (some equal)"){
        requireIsEqual("kurt(0, 1, 0, 1)", -2.4375);
    }

    SECTION("`kurtosis` Test (some negatives)"){
        requireIsEqual("kurtosis(1, -1, 7, -4, 5)", -1.9729537802265082);
    }

    SECTION("`kurtosis` Test (some negatives and zero)"){
        requireIsEqual("kurt(1, -3, 2, -5, 0)", -1.9757785467128033);
    }

    SECTION("`kurtosis` Test (positive, negative floats)"){
        requireIsEqual("kurtosis(1.0, -1.0, 2.0, -4.0, 5.0)", -1.6953152165400582);
    }

    SECTION("`kurtosis` Test (floats with zero)"){
        requireIsEqual("kurt(1.1, -1.2, 2.3, -4.4, 0)", -1.577289019731428);
    }

}

