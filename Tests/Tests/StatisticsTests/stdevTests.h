
#include "../EngineTest.h"

#include <Catch2>


TEST_CASE("Standard Deviation (ddof=1) Function Evaluation Tests", "[stdev]") {

    SECTION("Empty Test"){
        requireIsEqual("sd()", "Insufficient Number of Arguments for Function: sd");
    }

    SECTION("`stdev` Test (all equal)"){
        requireIsEqual("stdev(1, 1, 1, 1)", 0);
    }

    SECTION("`stdev` Test (some equal)"){
        requireIsEqual("std(0, 1, 0, 1)", sqrt(1.0/3.0));
    }

    SECTION("`stdev` Test (some negatives)"){
        requireIsEqual("sd(1, -1, 7, -4, 5)", sqrt(19.8));
    }

    SECTION("`stdev` Test (some negatives and zero)"){
        requireIsEqual("stdev(1, -3, 2, -5, 0)", sqrt(8.5));
    }

    SECTION("`stdev` Test (positive, negative floats)"){
        requireIsEqual("std(1.0, -1.0, 2.0, -4.0, 5.0)", sqrt(11.3));
    }

    SECTION("`stdev` Test (floats with zero)"){
        requireIsEqual("sd(1.0, -1.0, 2.0, -4.0, 0.0)", sqrt(5.3));
    }

    SECTION("`stdev` Test (floats with zero) 2"){
        requireIsEqual("sd(1.1, -1.2, 2.3, -4.4, 0)", 2.565735761920935);
    }
    
}
