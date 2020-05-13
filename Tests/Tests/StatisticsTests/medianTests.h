#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Median Function Evaluation Tests", "[median]") {

    // SECTION("`median` Empty Test"){
    //     requireIsEqual("median()", "Insufficient Number of Arguments for Function: median");
    // }

    SECTION("`median` Test 1"){
        requireIsEqual("median(0.75, 0.32, -3.08, 6.48, -1.99)", 0.32);
    }

    SECTION("`median` Test 2"){
        requireIsEqual("median(-1.39, -5.78, -7.97, 6.57, 3.25)", -1.39);
    }

    SECTION("`median` Test 3"){
        requireIsEqual("median(-6.6, -2.78, -5.73, -8.94, -5.42, 8.1, -3.41, 5.6)", -4.415);
    }

    SECTION("`median` Test 4"){
        requireIsEqual("median(-7.39, 6.42, -5.08)", -5.08);
    }

    SECTION("`median` Test 5"){
        requireIsEqual("median(7.15, 2.64, 1.95, -6.35, 4.1, -2.72, 0.62, 7.02, 2.92)", 2.64);
    }

    SECTION("`median` Test 6"){
        requireIsEqual("median(3.89, -1.31, 8.43, 1.46, 0.23, 5.17)", 2.675);
    }

    SECTION("`median` Test 7"){
        requireIsEqual("median(0.25, 9.48, -3.88, -5.47, 1.96)", 0.25);
    }

    SECTION("`median` Test 8"){
        requireIsEqual("median(-4.25, -0.74, -7.2, 7.68, -5.76, 3.38, -9.08, 0.76, 6.84)", -0.74);
    }

    SECTION("`median` Test 9"){
        requireIsEqual("median(8.96, -9.4, -1.8, -2.92, -8.92, 5.95)", -2.36);
    }

    SECTION("`median` Test 10"){
        requireIsEqual("median(9.13, 8.84, -0.59, -8.38, -9.94, -8.77)", -4.485);
    }

}
