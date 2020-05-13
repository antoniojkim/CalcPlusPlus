
#include "../EngineTest.h"

#include <Catch2>


TEST_CASE("Absolute Deviation Function Evaluation Tests", "[absdev]") {

    // SECTION("Empty Test"){
    //     requireIsEqual("absdev()", "Insufficient Number of Arguments for Function: absdev");
    // }

    SECTION("`absdev` Test 1"){
        requireIsEqual("absdev(5.59, 7.48, 3.03, 3.5, 9.49)", 2.1336);
    }

    SECTION("`absdev` Test 2"){
        requireIsEqual("absdev(8.49, -4.83, -8.12, 7.47)", 7.2275);
    }

    SECTION("`absdev` Test 3"){
        requireIsEqual("absdev(-9.67, -9.09)", 0.29);
    }

    SECTION("`absdev` Test 4"){
        requireIsEqual("absdev(0.67, 3.15, 0.17, 8.41, 6.83)", 3.0192);
    }

    SECTION("`absdev` Test 5"){
        requireIsEqual("absdev(4.76, 3.42)", 0.67);
    }

    SECTION("`absdev` Test 6"){
        requireIsEqual("absdev(0.09, -4.63, 0.84, -0.95, 5.82, 4.84, 6.8, 6.63, -1.56)", 3.5874074074);
    }

    SECTION("`absdev` Test 7"){
        requireIsEqual("absdev(-3.69, 3.77, -0.13)", 2.5244444444);
    }

    SECTION("`absdev` Test 8"){
        requireIsEqual("absdev(3.62, 7.52, 8.0, 2.98, -8.27, -8.19, 2.26, -9.25, -5.53)", 6.264691358);
    }

    SECTION("`absdev` Test 9"){
        requireIsEqual("absdev(-7.06, -6.06, -4.66, 6.21)", 4.55125);
    }

    SECTION("`absdev` Test 10"){
        requireIsEqual("absdev(3.07, -7.3, 4.21, 7.9)", 4.635);
    }

}
