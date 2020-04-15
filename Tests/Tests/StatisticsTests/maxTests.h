
#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Max Function Evaluation Tests", "[max]") {

    SECTION("Empty Test"){
        requireIsEqual("max()", "Insufficient Number of Arguments for Function: max");
    }

    SECTION("`max` Test (all equal)"){
        requireIsEqual("max(1, 1, 1, 1)", 1);
    }

    SECTION("`max` Test (some equal)"){
        requireIsEqual("max(0, 1, 0, 1)", 1);
    }

    SECTION("`max` Test (some negatives)"){
        requireIsEqual("max(1, -1, 7, -4, 5)", 7);
    }

    SECTION("`max` Test (some negatives and zero)"){
        requireIsEqual("max(1, -3, 2, -5, 0)", 2);
    }

    SECTION("`max` Test (positive, negative floats)"){
        requireIsEqual("max(1.0, -1.0, 2.0, -4.0, 5.0)", 5);
    }

    SECTION("`max` Test (floats with zero)"){
        requireIsEqual("max(1.1, -1.2, 2.3, -4.4, 0)", 2.3);
    }

}
