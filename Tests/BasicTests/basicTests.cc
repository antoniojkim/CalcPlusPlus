
#include "../EngineTest.h"

#include <Catch2>
#include <iostream>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

TEST_CASE("Basic Engine Evaluation Tests", "[test]" ) {

    requireIsEqual("1 + 3", 4);
    requireIsEqual("7 - 30", -23);
    requireIsEqual("3.4 * 7.2", 24.48);
    requireIsEqual("5.7 - 2.4 * 5.9", -8.46);
    requireIsEqual("5.7 + 2.4 / 5.9", 6.106779661);
    requireIsEqual("5.7 + 2.4 // 5.9", 5.7);
    requireIsEqual("5.7 + 5.9 // 2.4", 7.7);
    requireIsEqual("5.7 ^ 5.9", 28817.8547768);
    requireIsEqual("5.7 ** 5.9", 28817.8547768);

}
