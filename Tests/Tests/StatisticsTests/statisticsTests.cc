
#include "../EngineTest.h"

#include <Catch2>
#include <cmath>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Mean Function Evaluation Tests", "[mean]" ) {

    SECTION("`Empty Test"){
        requireIsEqual("mean()", "Insufficient Number of Arguments for Function: mean");
    }

    SECTION("`mean` Test (all equal)"){
        requireIsEqual("mean(1, 1, 1, 1)", 1);
    }

    SECTION("`mean` Test (some equal)"){
        requireIsEqual("mean(0, 1, 0, 1)", 0.5);
    }

    SECTION("`mean` Test (some negatives)"){
        requireIsEqual("mean(1, -1, 7, -4, 5)", 1.6);
    }

    SECTION("`mean` Test (some negatives and zero)"){
        requireIsEqual("mean(1, -3, 2, -5, 0)", -1);
    }

    SECTION("`mean` Test (positive, negative floats)"){
        requireIsEqual("mean(1.0, -1.0, 2.0, -4.0, 5.0)", 0.6);
    }

    SECTION("`mean` Test (floats with zero)"){
        requireIsEqual("mean(1.0, -1.0, 2.0, -4.0, 0.0)", -0.4);
    }

}


TEST_CASE("Variance Function Evaluation Tests", "[variance]" ) {

    SECTION("`Empty Test"){
        requireIsEqual("var()", "Insufficient Number of Arguments for Function: var");
    }

    SECTION("`var` Test (all equal)"){
        requireIsEqual("var(1, 1, 1, 1)", 0);
    }

    SECTION("`var` Test (some equal)"){
        requireIsEqual("variance(0, 1, 0, 1)", 1.0/3.0);
    }

    SECTION("`var` Test (some negatives)"){
        requireIsEqual("var(1, -1, 7, -4, 5)", 19.8);
    }

    SECTION("`var` Test (some negatives and zero)"){
        requireIsEqual("var(1, -3, 2, -5, 0)", 8.5);
    }

    SECTION("`var` Test (positive, negative floats)"){
        requireIsEqual("variance(1.0, -1.0, 2.0, -4.0, 5.0)", 11.3);
    }

    SECTION("`var` Test (floats with zero)"){
        requireIsEqual("var(1.0, -1.0, 2.0, -4.0, 0.0)", 5.3);
    }

}


TEST_CASE("Standard Deviation Function Evaluation Tests", "[variance]" ) {

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

}
