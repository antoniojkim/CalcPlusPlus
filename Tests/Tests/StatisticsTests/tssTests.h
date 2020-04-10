
#include "../EngineTest.h"

#include <Catch2>


TEST_CASE("Total Sum of Squares Function Evaluation Tests", "[tss]") {
    
    SECTION("Empty Test"){
        requireIsEqual("tss()", "Insufficient Number of Arguments for Function: tss");
    }

    SECTION("`tss` Test 1"){
        requireIsEqual("tss(-7.77, 8.6, 3.45, 1.96, -0.8, 8.84, -2.4, -1.22)", 221.90655);
    }

    SECTION("`tss` Test 2"){
        requireIsEqual("tss(8.6, -5.77, -3.88)", 121.9398);
    }

    SECTION("`tss` Test 3"){
        requireIsEqual("tss(-5.28, 6.3, 8.85, 2.53, 0.59, 7.75, 1.15)", 145.5717428571);
    }

    SECTION("`tss` Test 4"){
        requireIsEqual("tss(9.67, 9.96, 1.58, 6.49, -8.95, -6.56)", 335.6970833333);
    }

    SECTION("`tss` Test 5"){
        requireIsEqual("tss(-1.04, 4.78, 8.25, 0.96)", 50.988475);
    }

    SECTION("`tss` Test 6"){
        requireIsEqual("tss(1.07, -5.03, -4.43, -9.62, 1.45, 7.02, 2.23, 2.23)", 196.718);
    }

    SECTION("`tss` Test 7"){
        requireIsEqual("tss(-4.77, 6.74)", 66.24005);
    }

    SECTION("`tss` Test 8"){
        requireIsEqual("tss(6.44, -9.9, -4.17)", 137.4668666667);
    }

    SECTION("`tss` Test 9"){
        requireIsEqual("tss(-3.77, 9.78, 6.69)", 100.8540666667);
    }

    SECTION("`tss` Test 10"){
        requireIsEqual("tss(5.3, 0.04, -3.5, 0.89, -0.66, 9.14, -7.0)", 171.5768857143);
    }

}

