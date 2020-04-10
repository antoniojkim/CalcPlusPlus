
#include "../EngineTest.h"

#include <Catch2>


TEST_CASE("Standard Deviation (ddof=1) Function Evaluation Tests", "[stdev]") {

    SECTION("Empty Test"){
        requireIsEqual("sd()", "Insufficient Number of Arguments for Function: sd");
    }

    SECTION("`std` Test 1"){
        requireIsEqual("std(-2.59, 3.95)", 4.624478349);
    }

    SECTION("`sd` Test 2"){
        requireIsEqual("sd(-9.67, 7.38, -4.87)", 8.7920892473);
    }

    SECTION("`stdev` Test 3"){
        requireIsEqual("stdev(0.06, -8.43, -7.82, -8.21, -0.78, -0.75)", 4.2127208152);
    }

    SECTION("`std` Test 4"){
        requireIsEqual("std(1.02, -7.32)", 5.8972705551);
    }

    SECTION("`std` Test 5"){
        requireIsEqual("std(1.74, 2.63)", 0.6293250353);
    }

    SECTION("`stdev` Test 6"){
        requireIsEqual("stdev(-2.18, 4.35)", 4.6174072811);
    }

    SECTION("`std` Test 7"){
        requireIsEqual("std(1.25, -8.93)", 7.1983470325);
    }

    SECTION("`sd` Test 8"){
        requireIsEqual("sd(-3.76, 7.57, -4.01, -2.7, 8.58, 9.67, -8.7)", 7.4309084236);
    }

    SECTION("`sd` Test 9"){
        requireIsEqual("sd(-1.81, 0.47, -2.18, -7.88, 2.67, -0.29, -2.96, -5.74, -0.13)", 3.2380626924);
    }

    SECTION("`sd` Test 10"){
        requireIsEqual("sd(-8.89, 0.76, -5.74, -0.48, -4.62, 4.52, 6.05)", 5.4937085228);
    }
    
}
