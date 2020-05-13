
#include "../EngineTest.h"

#include <Catch2>

#include <gsl/gsl_math.h>

TEST_CASE("kurtosis Function Evaluation Tests", "[kurtosis]") {

    // SECTION("Empty Test"){
    //     requireIsEqual("kurtosis()", "Insufficient Number of Arguments for Function: kurtosis");
    // }

    SECTION("`kurtosis` Test 1"){
        requireIsEqual("kurtosis(-9.75, -6.89, 8.71, 9.56)", -2.4054875147);
    }

    SECTION("`kurtosis` Test 2"){
        requireIsEqual("kurtosis(-0.03, -0.66, 8.08, 7.46, -9.47, 5.48)", -1.3867096466);
    }

    SECTION("`kurt` Test 3"){
        requireIsEqual("kurt(6.88, 2.73, 0.91, 7.03)", -2.3097016758);
    }

    SECTION("`kurt` Test 4"){
        requireIsEqual("kurt(8.51, 4.35)", -2.75);
    }

    SECTION("`kurtosis` Test 5"){
        requireIsEqual("kurtosis(9.24, -5.27, 8.46, 8.69, 3.49, 7.69)", -0.7621422371);
    }

    SECTION("`kurt` Test 6"){
        requireIsEqual("kurt(0.94, 2.67, -0.5, -4.74)", -1.8915463404);
    }

    SECTION("`kurt` Test 7"){
        requireIsEqual("kurt(-3.29, -3.04, 2.81, 6.5, -2.0)", -1.8864498289);
    }

    SECTION("`kurtosis` Test 8"){
        requireIsEqual("kurtosis(-9.95, -8.32, 3.62, -9.95)", -1.7095361309);
    }

    SECTION("`kurtosis` Test 9"){
        requireIsEqual("kurtosis(-2.47, 7.98, 7.08, 5.36, -0.13, 0.57, -5.41, -6.09, -4.31)", -1.7566598859);
    }

    SECTION("`kurtosis` Test 10"){
        requireIsEqual("kurtosis(-3.21, -8.75, 6.86, 9.35, -3.09, 4.99)", -1.932477903);
    }

}
