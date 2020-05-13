
#include "../EngineTest.h"

#include <Catch2>

#include <gsl/gsl_math.h>

TEST_CASE("Lag-1 Autocorrelate Function Evaluation Tests", "[lag1]") {

    // SECTION("Empty Test"){
    //     requireIsEqual("lag1()", "Insufficient Number of Arguments for Function: lag1");
    // }

    SECTION("`lag1` Test 1"){
        requireIsEqual("lag1(3.95, 6.81, -3.05, -1.64, -3.5, 4.95, -8.23, 2.92, 6.06)", -0.2164409953);
    }

    SECTION("`autocorr` Test 2"){
        requireIsEqual("autocorr(1.61, 7.86, -2.26, -5.62, 8.1, -4.55, 8.97)", -0.5295711223);
    }

    SECTION("`autocorr` Test 3"){
        requireIsEqual("autocorr(-2.79, -2.1)", -0.5);
    }

    SECTION("`autocorr` Test 4"){
        requireIsEqual("autocorr(7.27, -7.71, -6.63, -6.2, -0.98, 4.56)", 0.0020706076);
    }

    SECTION("`lag1` Test 5"){
        requireIsEqual("lag1(8.81, -2.71)", -0.5);
    }

    SECTION("`lag1` Test 6"){
        requireIsEqual("lag1(5.72, -3.33, 9.2, 2.92, -9.47, -8.05, -3.63)", 0.153525765);
    }

    SECTION("`autocorr` Test 7"){
        requireIsEqual("autocorr(1.85, 6.89, -9.39, 5.94, -7.5)", -0.657389584);
    }

    SECTION("`autocorr` Test 8"){
        requireIsEqual("autocorr(-5.14, -7.63, 5.89, 0.62, -1.38, 8.92, 7.13)", 0.1620685975);
    }

    SECTION("`autocorr` Test 9"){
        requireIsEqual("autocorr(-3.61, 8.1, -9.53, -6.09, -1.66, 2.79, 7.55)", -0.0886150351);
    }

    SECTION("`lag1` Test 10"){
        requireIsEqual("lag1(-0.76, 0.63)", -0.5);
    }

}
