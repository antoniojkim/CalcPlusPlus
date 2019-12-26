
#include "../EngineTest.h"

#include <Catch2>
#include <string>
#include <gsl/gsl_math.h>

using namespace std;

void basicTest(const string& input, const double& expected){
    auto expression = engine.eval(input);
    REQUIRE( gsl_fcmp(expression->value(), expected, 1e-6) );
}

TEST_CASE("Basic Engine Evaluation Tests", "[scanner]" ) {

    basicTest("1 + 3", 4);

}
