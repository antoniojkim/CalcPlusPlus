
#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Min Function Evaluation Tests", "[min]") {

    SECTION("Empty Test"){
        requireIsEqual("min()", "Insufficient Number of Arguments for Function: min");
    }

    SECTION("`min` Test (all equal)"){
        requireIsEqual("min(1, 1, 1, 1)", 1);
    }

    SECTION("`min` Test (some equal)"){
        requireIsEqual("min(0, 1, 0, 1)", 0);
    }

    SECTION("`min` Test (some negatives)"){
        requireIsEqual("min(1, -1, 7, -4, 5)", -4);
    }

    SECTION("`min` Test (some negatives and zero)"){
        requireIsEqual("min(1, -3, 2, -5, 0)", -5);
    }

    SECTION("`min` Test (positive, negative floats)"){
        requireIsEqual("min(1.0, -1.0, 2.0, -4.0, 5.0)", -4);
    }

    SECTION("`min` Test (floats with zero)"){
        requireIsEqual("min(1.1, -1.2, 2.3, -4.4, 0)", -4.4);
    }

}
