
using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Syntax Error Tests", "[syntax]" ) {

    requireErrorIsEqual("quad(1, 2, -", "Cannot construct Tuple from empty list of expressions");
    requireErrorIsEqual("quad(-", "Function 'neg' found no argument");
    requireErrorIsEqual("quad(,", "comma separator found no preceding expression");

    requireErrorIsEqual("SVD{)", "Mismatched Parentheses: ')'");

    requireErrorIsEqual("{{", "Matrix must be two dimensional");

    requireErrorIsEqual("TEST(3)", "Invalid Function: TEST");

    requireErrorIsEqual("integral(e^(-", "Cannot construct Tuple from empty list of expressions");
    requireErrorIsEqual("integral(e^(-x", "integral: non-default argument follows default argument");
    requireErrorIsEqual("integral(e^(-x^", "Insufficient Number of Arguments for Binary Operator: ^");
    requireErrorIsEqual("integral(e^(-x^2", "integral: non-default argument follows default argument");
}
