

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Complex Operators Tests", "[complexOperators]" ) {

    SECTION("`complex addition` Test"){
        requireExprIsEqual("(-8.61-0.47i) + (-9.22-8.36i)", "-17.83-8.83");
    }
    SECTION("`complex subtraction` Test"){
        requireExprIsEqual("(-8.27-2.38i) - (0.12-7.46i)", "-8.39+5.08");
    }
    SECTION("`complex multiplication` Test"){
        requireExprIsEqual("(7.59-6.57i) * (8.44-2.66i)", "46.5834-75.6402");
    }
    SECTION("`complex division` Test"){
        requireExprIsEqual("(8.69+9.84i) / (-8.41+5.27i)", "-0.2154912133-1.3050699993");
    }

}
