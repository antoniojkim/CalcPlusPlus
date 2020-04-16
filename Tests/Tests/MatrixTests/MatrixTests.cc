

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Matrix Determinant Tests", "[det]" ) {

    requireIsEqual("det({{3, 4}, {2, 1}})", -5);
    requireIsEqual("det{{3, 4}, {2, 1}}", -5);

    requireIsEqual("det({{9, 3, 5}, {-6, -9, 7}, {-1, -8, 1}})", 615);
    requireIsEqual("det{{9, 3, 5}, {-6, -9, 7}, {-1, -8, 1}}", 615);

    requireIsEqual("det({{9.1, 3.2, 5.3}, {-6.4, -9.5, 7.6}, {-1.7, -8.8, 1.9}})", 654.822);
    requireIsEqual("det{{9.1, 3.2, 5.3}, {-6.4, -9.5, 7.6}, {-1.7, -8.8, 1.9}}", 654.822);

}

TEST_CASE("Matrix Multiplication Tests", "[matmul]" ) {

    requireIsEqual("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}}",
                   vector<vector<double>>{{367.76, 368.12}, {674.06, 674.72}});

}
