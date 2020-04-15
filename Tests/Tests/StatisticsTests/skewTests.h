
#include "../EngineTest.h"

#include <Catch2>

#include <gsl/gsl_math.h>

TEST_CASE("Skew Function Evaluation Tests", "[skew]") {

    SECTION("Empty Test"){
        requireIsEqual("skew()", "Insufficient Number of Arguments for Function: skew");
    }

    SECTION("`skew` Test 1"){
        requireIsEqual("skew(-7.48, 1.3, -6.68, 7.61, -3.75)", 0.4478899957);
    }

    SECTION("`skew` Test 2"){
        requireIsEqual("skew(-9.79, 6.39, -2.51, 5.03, -7.83, -5.82, 5.14)", 0.0115605537);
    }

    SECTION("`skew` Test 3"){
        requireIsEqual("skew(-8.75, -8.67, 6.72, -4.01, -0.14, -2.32, 7.62, -7.36, 9.19)", 0.2380296624);
    }

    SECTION("`skew` Test 4"){
        requireIsEqual("skew(8.28, -5.77, -5.76)", 0.3848995209);
    }

    SECTION("`skew` Test 5"){
        requireIsEqual("skew(-7.03, 4.48, -2.21, 6.56, -3.27, 6.23, -3.57, 9.99, 0.48)", 0.0727451398);
    }

    SECTION("`skew` Test 6"){
        requireIsEqual("skew(-5.52, -5.18, -0.97, -0.07)", 0.0281579987);
    }

    SECTION("`skew` Test 7"){
        requireIsEqual("skew(5.24, -9.46, 1.35, -5.8, 4.4, 3.6)", -0.5210503622);
    }

    SECTION("`skew` Test 8"){
        requireIsEqual("skew(4.94, -2.29, 7.81, 8.51, -5.59, -6.55, 5.24)", -0.2249073199);
    }

    SECTION("`skew` Test 9"){
        requireIsEqual("skew(-3.73, -9.06, -4.36, 6.63, -4.59)", 0.6907748203);
    }

    SECTION("`skew` Test 10"){
        requireIsEqual("skew(-5.79, -1.84, -6.12, -5.07, -2.07, -3.48, 9.85, -6.41)", 1.4695482561);
    }

}
