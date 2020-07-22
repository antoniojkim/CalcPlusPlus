
using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Syntax Error Tests", "[syntax]" ) {

    requireErrorIsEqual("quad(-", "Function 'neg' found no argument");
    requireErrorIsEqual("quad(,", "comma separator found no preceding expression");

    requireErrorIsEqual("SVD{)", "Mismatched Parentheses: ')'");

    requireErrorIsEqual("{{", "Matrix must be two dimensional");

    requireErrorIsEqual("TEST(3)", "Invalid Function: TEST");
}
