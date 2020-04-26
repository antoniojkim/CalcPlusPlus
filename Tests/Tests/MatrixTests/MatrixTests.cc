

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
        requireIsEqual("2i + {{1, 2}, {3, 4}}", vector<vector<gsl_complex>>{{{1, 2}, {2, 2}}, {{3, 2}, {4, 2}}});
    }
    SECTION("Matrix Scalar Subtraction"){
        requireIsEqual("{{1, 2}, {3, 4}} - 2", vector<vector<double>>{{-1, 0}, {1, 2}});
        requireIsEqual("2 - {{1, 2}, {3, 4}}", vector<vector<double>>{{1, 0}, {-1, -2}});
        requireIsEqual("2 - {{1, 2i}, {3, 4i}}", vector<vector<gsl_complex>>{{{1, 0}, {2, -2}}, {{-1, 0}, {2, -4}}});
    }
    SECTION("Matrix Scalar Multiplication"){
        requireIsEqual("{{1, 2}, {3, 4}} * 2", vector<vector<double>>{{2, 4}, {6, 8}});
        requireIsEqual("2 * {{1, 2}, {3, 4}}", vector<vector<double>>{{2, 4}, {6, 8}});
        requireIsEqual("{{i, 2}, {3i, 4}} * 2i", vector<vector<gsl_complex>>{{{-2, 0}, {0, 4}}, {{-6, 0}, {0, 8}}});
    }
    SECTION("Matrix Scalar Division"){
        requireIsEqual("{{1, 2}, {3, 4}} / 2", vector<vector<double>>{{0.5, 1}, {1.5, 2}});
        requireIsEqual("2 / {{1, 2}, {3, 4}}", vector<vector<double>>{{2, 1}, {2.0/3.0, 0.5}});
    }

}

TEST_CASE("Matrix Transpose Tests", "[transpose]"){

    SECTION("Real Matrix Transpose Tests"){
        requireIsEqual("{{1, 2}, {3, 4}}^T", vector<vector<double>>{{1, 3}, {2, 4}});
        requireIsEqual("{{1, 2, 3}, {4, 5, 6}}^T", vector<vector<double>>{{1, 4}, {2, 5}, {3, 6}});
    }

    SECTION("Complex Matrix Transpose Tests"){
        requireIsEqual("{{1+2i, 2-5i}, {3, 4}}^T", vector<vector<gsl_complex>>{{{1, 2}, {3, 0}}, {{2, -5}, {4, 0}}});
        requireIsEqual("{{1, 2, 3i}, {4, 5, 6}}^T", vector<vector<gsl_complex>>{{{1, 0}, {4, 0}}, {{2, 0}, {5, 0}}, {{0, 3}, {6, 0}}});
    }

}

TEST_CASE("Matrix Inverse Tests", "[transpose]"){

    SECTION("Real Matrix Inverse Tests"){
        requireIsEqual("{{1, 2}, {3, 4}}^-1", vector<vector<double>>{{-2, 1}, {1.5, -0.5}});
        requireIsEqual("{{10, -9, -12}, {7, -12, 11}, {-10, 10, 3}}^-1", vector<vector<double>>{{-146./319, -93./319, -243./319}, {-131./319, -90./319, -194./319}, {-50./319, -10./319, -57./319}});
    }

    SECTION("Complex Matrix Inverse Tests"){
        requireIsEqual("{{1i, 2}, {3, 4i}}^-1", vector<vector<gsl_complex>>{{{0.0, -0.4},{0.2, 0.0}},  {{0.3, 0.0},{0.0, -0.1}}});
        requireIsEqual("{{10, -9i, -12}, {7, -12, 11i}, {-10i, 10, 3}}^-1", vector<vector<gsl_complex>>{{{0.0568283247, 0.0698351186},{0.0796074604, -0.0530825327},   {0.0326773457, -0.012553547}},  {{-0.0646285282, 0.0248281262},{0.0116912281, 0.0955086199},   {0.0916841601, 0.0564446685}},  {{-0.0173553014, 0.1066673283},{0.1379710152, -0.053003865},   {0.0695646228, -0.0792244093}}});
    }

}
