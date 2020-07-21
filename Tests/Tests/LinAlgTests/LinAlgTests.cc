

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

TEST_CASE("LU Decomposition Tests", "[LU]") {

    requireExprIsEqual("LU{{1, 1, 1}, {1, -2, 2}, {1, 2, -1}}",
                       "(LU = {{1, 1, 1}, {1, -3, 1}, {1, -1/3, -5/3}}, P = {0, 1, 2}, sign = 1)");

}

TEST_CASE("Cholesky Decomposition Tests", "[cholesky]") {

    requireExprIsEqual("Cholesky{{9, 3, 0}, {3, 5, 2}, {0, 2, 17}}", "{{3, 3, 0}, {1, 2, 2}, {0, 1, 4}}");

}
