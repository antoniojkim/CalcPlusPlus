
#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("argmax Function Evaluation Tests", "[argmax]") {

    SECTION("Empty Test"){
        requireIsEqual("argmax()", "Insufficient Number of Arguments for Function: argmax");
    }

    SECTION("`argmax` Test 1"){
        requireIsEqual("argmax(-2.2, -9.94, 4.02, -7.83)", 2);
    }

    SECTION("`argmax` Test 2"){
        requireIsEqual("argmax(-4.75, -2.11, -4.75)", 1);
    }

    SECTION("`argmax` Test 3"){
        requireIsEqual("argmax(1.11, -2.48, 3.09, -3.59, -2.53, 8.42, -4.51)", 5);
    }

    SECTION("`argmax` Test 4"){
        requireIsEqual("argmax(2.04, -6.72, -1.32, 5.78, -0.49)", 3);
    }

    SECTION("`argmax` Test 5"){
        requireIsEqual("argmax(1.27, -5.28, 9.15, 4.05, 6.4, -7.27, -6.28, -7.26, -5.93)", 2);
    }

    SECTION("`argmax` Test 6"){
        requireIsEqual("argmax(-8.86, -5.21, -2.38)", 2);
    }

    SECTION("`argmax` Test 7"){
        requireIsEqual("argmax(6.26, 2.97, -1.89, -7.16, 1.8, -6.56)", 0);
    }

    SECTION("`argmax` Test 8"){
        requireIsEqual("argmax(-1.61, 2.67, -7.17, 8.28, -9.63)", 3);
    }

    SECTION("`argmax` Test 9"){
        requireIsEqual("argmax(6.35, -5.85, 3.82, 5.33, -1.64, -5.35)", 0);
    }

    SECTION("`argmax` Test 10"){
        requireIsEqual("argmax(6.67, 8.93, -8.98, -3.13, 0.14, 9.07, -7.05, 9.08)", 7);
    }

}
