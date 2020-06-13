

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Tuple Expression Tests", "[TupleTests]" ) {

    requireIsEqual("(1, 2, 3, 4)", "(1, 2, 3, 4)");
    requireIsEqual("mean((1, 2, 3, 4))", "mean(1, 2, 3, 4)");
    requireIsEqual("mean((1, 2, 3, 4))", 2.5);
    requireExprIsEqual("quad(-0.59, -0.47, -1.3)", "()");

}
