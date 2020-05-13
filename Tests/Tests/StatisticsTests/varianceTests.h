#include "../EngineTest.h"

#include <Catch2>

TEST_CASE("Variance Function Evaluation Tests", "[variance]") {

    // SECTION("`Empty Test"){
    //     requireIsEqual("var()", "Insufficient Number of Arguments for Function: var");
    // }

    SECTION("`var` Test 1"){
        requireIsEqual("var(4.13, -3.23, -3.77)", 19.4785333333);
    }

    SECTION("`var` Test 2"){
        requireIsEqual("var(-3.37, -0.06, 0.12, 8.23, 3.73, -7.46)", 29.6872566667);
    }

    SECTION("`var` Test 3"){
        requireIsEqual("var(-0.31, -7.7, 7.67, -3.88, -8.21, 8.38, -7.17, 6.88, -2.49)", 46.3322611111);
    }

    SECTION("`var` Test 4"){
        requireIsEqual("var(-3.4, -4.29, 5.3, -1.14, -9.51, 1.59, -0.77, -4.22, 4.97)", 22.6007777778);
    }

    SECTION("`var` Test 5"){
        requireIsEqual("var(-0.35, -5.24, 6.37, -6.78, 2.99, -0.46)", 24.2540566667);
    }

    SECTION("`var` Test 6"){
        requireIsEqual("var(-3.28, -2.15, 9.22, -4.48, 1.48, 9.18, -6.63, 8.54)", 43.7384571429);
    }

    SECTION("`var` Test 7"){
        requireIsEqual("var(1.91, 9.06, 9.81, 3.18)", 16.1866);
    }

    SECTION("`var` Test 8"){
        requireIsEqual("var(-4.39, -2.32, 3.67, 6.1, -5.42, 1.98, 2.74)", 19.2236904762);
    }

    SECTION("`var` Test 9"){
        requireIsEqual("var(-8.84, -6.28, 8.82, -5.62, 6.81, -4.04, 9.89, 1.7)", 55.6594857143);
    }

    SECTION("`var` Test 10"){
        requireIsEqual("var(-1.1, 4.25, 9.45, -0.47, 3.46, -6.83)", 30.92536);
    }

}
