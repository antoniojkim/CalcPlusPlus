#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Mean Function Evaluation Tests", "[mean]") {

    // SECTION("`Empty Test"){
    //     requireIsEqual("mean()", "Insufficient Number of Arguments for Function: mean");
    // }

    SECTION("`mean` Test 1"){
        requireIsEqual("mean(3.93, -9.89, 4.34, 3.89, 6.51, 5.45)", 2.3716666667);
    }

    SECTION("`mean` Test 2"){
        requireIsEqual("mean(-1.78, 4.45, -5.46, -1.19, 1.33, 6.93)", 0.7133333333);
    }

    SECTION("`mean` Test 3"){
        requireIsEqual("mean(-9.58, 2.9, -6.6, 2.88, 4.78, -6.29, -9.68)", -3.0842857143);
    }

    SECTION("`mean` Test 4"){
        requireIsEqual("mean(7.26, 1.68)", 4.47);
    }

    SECTION("`mean` Test 5"){
        requireIsEqual("mean(7.56, 3.36, -5.61, -8.2, 7.75, -1.68, 5.98, 1.33, 9.68)", 2.2411111111);
    }

    SECTION("`mean` Test 6"){
        requireIsEqual("mean(-5.48, -2.04, 2.93, 8.83, -0.23, -7.05, -2.18, 9.53)", 0.53875);
    }

    SECTION("`mean` Test 7"){
        requireIsEqual("mean(3.79, -5.61, 8.21, 5.66, -6.5)", 1.11);
    }

    SECTION("`mean` Test 8"){
        requireIsEqual("mean(-6.91, -5.55, -8.42)", -6.96);
    }

    SECTION("`mean` Test 9"){
        requireIsEqual("mean(-1.42, 7.41, -5.47, -2.33, 9.33, -3.92)", 0.6);
    }

    SECTION("`mean` Test 10"){
        requireIsEqual("mean(-4.86, 5.67, -0.86, -2.96, 1.83, -6.98, 1.2)", -0.9942857143);
    }

}
