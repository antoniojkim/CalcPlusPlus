

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Complex Operators Tests", "[complexOperators]" ) {

    SECTION("`complex addition` Test"){
        requireIsEqual("(-8.61-0.47i) + (-9.22-8.36i)", gsl_complex{-17.83, -8.83});
    }
    SECTION("`complex subtraction` Test"){
        requireIsEqual("(-8.27-2.38i) - (0.12-7.46i)", gsl_complex{-8.39, 5.08});
    }
    SECTION("`complex multiplication` Test"){
        requireIsEqual("(7.59-6.57i) * (8.44-2.66i)", gsl_complex{46.5834, -75.6402});
    }
    SECTION("`complex division` Test"){
        requireIsEqual("(8.69+9.84i) / (-8.41+5.27i)", gsl_complex{-0.2154912133, -1.3050699993});
    }

}