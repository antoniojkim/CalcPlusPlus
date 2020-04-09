
#include "../EngineTest.h"

#include <Catch2>


TEST_CASE("Total Sum of Squares Function Evaluation Tests", "[tss]") {
    
    SECTION("Empty Test"){
        requireIsEqual("tss()", "Insufficient Number of Arguments for Function: tss");
    }

    SECTION("`tss` Test (all equal)"){
        requireIsEqual("tss(1, 1, 1, 1)", 0);
    }

    SECTION("`tss` Test (some equal)"){
        requireIsEqual("tss(0, 1, 0, 1)", 1);
    }

    SECTION("`tss` Test (some negatives)"){
        requireIsEqual("tss(1, -1, 7, -4, 5)", 79.2);
    }

    SECTION("`tss` Test (some negatives and zero)"){
        requireIsEqual("tss(1, -3, 2, -5, 0)", 34);
    }

    SECTION("`tss` Test (positive, negative floats)"){
        requireIsEqual("tss(1.0, -1.0, 2.0, -4.0, 5.0)", 45.2);
    }

    SECTION("`tss` Test (floats with zero)"){
        requireIsEqual("tss(1.1, -1.2, 2.3, -4.4, 0)", 26.332);
    }

}

