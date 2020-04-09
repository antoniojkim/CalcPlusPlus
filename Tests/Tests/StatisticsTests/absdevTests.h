
#include "../EngineTest.h"

#include <Catch2>


TEST_CASE("Absolute Deviation Function Evaluation Tests", "[absdev]") {
    
    SECTION("Empty Test"){
        requireIsEqual("absdev()", "Insufficient Number of Arguments for Function: absdev");
    }

    SECTION("`absdev` Test (all equal)"){
        requireIsEqual("absdev(1, 1, 1, 1)", 0);
    }

    SECTION("`absdev` Test (some equal)"){
        requireIsEqual("absdev(0, 1, 0, 1)", 0.5);
    }

    SECTION("`absdev` Test (some negatives)"){
        requireIsEqual("absdev(1, -1, 7, -4, 5)", 3.52);
    }

    SECTION("`absdev` Test (some negatives and zero)"){
        requireIsEqual("absdev(1, -3, 2, -5, 0)", 2.4);
    }

    SECTION("`absdev` Test (positive, negative floats)"){
        requireIsEqual("absdev(1.0, -1.0, 2.0, -4.0, 5.0)", 2.48);
    }

    SECTION("`absdev` Test (floats with zero)"){
        requireIsEqual("absdev(1.1, -1.2, 2.3, -4.4, 0)", 1.888);
    }

}

