

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

TEST_CASE("SVD Tests", "[svd]") {

    requireExprIsEqual("SVD{{4, 0}, {0, -1}}", "(U = {{1, 0}, {0, 1}}, S = {{4}, {1}}, V = {{1, 0}, {0, -1}})");
    requireExprIsEqual("SVD{{3, 0}, {0, 2}}", "(U = {{1, 0}, {0, 1}}, S = {{3}, {2}}, V = {{1, 0}, {0, 1}})");

}

TEST_CASE("QR Tests", "[qr]") {

    requireExprIsEqual("QR({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}})", "(Q = {{-6/7, 69/175, 58/175}, {-3/7, -158/175, -6/175}, {2/7, -6/35, 33/35}}, R = {{-14, -21, 14}, {0, -175, 70}, {0, 0, -35}})");

}
