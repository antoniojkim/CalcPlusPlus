

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
    requireIsEqual("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}} * {{1, 2}, {3, 4}}",
                   vector<vector<double>>{{1472.12, 2208}, {2698.22, 4047}});
    requireIsEqual("det({{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}})", 0.06);
    requireIsEqual("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012, 1021}, {1022, 1031, 1032}}",
                   vector<vector<double>>{{111.21, 121.44, 132.73}, {214.62, 226.82, 237.36}});

}

TEST_CASE("Matrix Scalar Operation Tests", "[matscalar]"){

    SECTION("Matrix Scalar Addition"){
        requireIsEqual("{{1, 2}, {3, 4}} + 2", vector<vector<double>>{{3, 4}, {5, 6}});
        requireIsEqual("2 + {{1, 2}, {3, 4}}", vector<vector<double>>{{3, 4}, {5, 6}});
    }
    SECTION("Matrix Scalar Subtraction"){
        requireIsEqual("{{1, 2}, {3, 4}} - 2", vector<vector<double>>{{-1, 0}, {1, 2}});
        requireIsEqual("2 - {{1, 2}, {3, 4}}", vector<vector<double>>{{1, 0}, {-1, -2}});
    }
    SECTION("Matrix Scalar Multiplication"){
        requireIsEqual("{{1, 2}, {3, 4}} * 2", vector<vector<double>>{{2, 4}, {6, 8}});
        requireIsEqual("2 * {{1, 2}, {3, 4}}", vector<vector<double>>{{2, 4}, {6, 8}});
    }
    SECTION("Matrix Scalar Division"){
        requireIsEqual("{{1, 2}, {3, 4}} / 2", vector<vector<double>>{{0.5, 1}, {1.5, 2}});
        requireIsEqual("2 / {{1, 2}, {3, 4}}", vector<vector<double>>{{2, 1}, {2.0/3.0, 0.5}});
    }

}
