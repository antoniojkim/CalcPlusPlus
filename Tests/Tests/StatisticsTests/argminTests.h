
#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("argmin Function Evaluation Tests", "[argmin]") {

    // SECTION("Empty Test"){
    //     requireIsEqual("argmin()", "Insufficient Number of Arguments for Function: argmin");
    // }

    SECTION("`argmin` Test 1"){
        requireIsEqual("argmin(8.33, 8.71, 4.39, 1.86, 3.59)", 3);
    }

    SECTION("`argmin` Test 2"){
        requireIsEqual("argmin(8.45, 3.83, -8.85)", 2);
    }

    SECTION("`argmin` Test 3"){
        requireIsEqual("argmin(2.12, -6.85)", 1);
    }

    SECTION("`argmin` Test 4"){
        requireIsEqual("argmin(-1.23, 5.94)", 0);
    }

    SECTION("`argmin` Test 5"){
        requireIsEqual("argmin(9.85, 7.94, -0.2, -6.91, 3.67, 8.78)", 3);
    }

    SECTION("`argmin` Test 6"){
        requireIsEqual("argmin(-9.39, 8.55, -5.25, 4.05, -5.72, -0.17, 5.36)", 0);
    }

    SECTION("`argmin` Test 7"){
        requireIsEqual("argmin(-0.08, 4.41, 8.72, 1.91, -3.27, -4.37, 2.17, -8.92)", 7);
    }

    SECTION("`argmin` Test 8"){
        requireIsEqual("argmin(5.3, -8.24, -8.0, -6.49, 9.93, -8.05, -4.54, -9.37, 2.28)", 7);
    }

    SECTION("`argmin` Test 9"){
        requireIsEqual("argmin(7.26, -4.35, 9.7, 0.45, -5.8, -1.74, -1.56, -0.94, -8.65)", 8);
    }

    SECTION("`argmin` Test 10"){
        requireIsEqual("argmin(0.79, 1.41, 5.05, 5.06)", 0);
    }

}
