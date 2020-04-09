#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Mean Function Evaluation Tests", "[mean]") {

    SECTION("`Empty Test"){
        requireIsEqual("mean()", "Insufficient Number of Arguments for Function: mean");
    }

    SECTION("`mean` Test (all equal)"){
        requireIsEqual("mean(1, 1, 1, 1)", 1);
    }

    SECTION("`mean` Test (some equal)"){
        requireIsEqual("mean(0, 1, 0, 1)", 0.5);
    }

    SECTION("`mean` Test (some negatives)"){
        requireIsEqual("mean(1, -1, 7, -4, 5)", 1.6);
    }

    SECTION("`mean` Test (some negatives and zero)"){
        requireIsEqual("mean(1, -3, 2, -5, 0)", -1);
    }

    SECTION("`mean` Test (positive, negative floats)"){
        requireIsEqual("mean(1.0, -1.0, 2.0, -4.0, 5.0)", 0.6);
    }

    SECTION("`mean` Test (floats with zero)"){
        requireIsEqual("mean(1.0, -1.0, 2.0, -4.0, 0.0)", -0.4);
    }

}
