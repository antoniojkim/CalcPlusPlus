#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Variance Function Evaluation Tests", "[variance]") {

    SECTION("`Empty Test"){
        requireIsEqual("var()", "Insufficient Number of Arguments for Function: var");
    }

    SECTION("`var` Test (all equal)"){
        requireIsEqual("var(1, 1, 1, 1)", 0);
    }

    SECTION("`var` Test (some equal)"){
        requireIsEqual("variance(0, 1, 0, 1)", 1.0/3.0);
    }

    SECTION("`var` Test (some negatives)"){
        requireIsEqual("var(1, -1, 7, -4, 5)", 19.8);
    }

    SECTION("`var` Test (some negatives and zero)"){
        requireIsEqual("var(1, -3, 2, -5, 0)", 8.5);
    }

    SECTION("`var` Test (positive, negative floats)"){
        requireIsEqual("variance(1.0, -1.0, 2.0, -4.0, 5.0)", 11.3);
    }

    SECTION("`var` Test (floats with zero)"){
        requireIsEqual("var(1.0, -1.0, 2.0, -4.0, 0.0)", 5.3);
    }

}
