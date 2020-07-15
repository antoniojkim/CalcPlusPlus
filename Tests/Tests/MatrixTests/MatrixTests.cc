

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Matrix Multiplication Tests", "[matmul]" ) {

    requireExprIsEqual("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}}",
                       "{{367.76, 368.12}, {674.06, 674.72}}");
    requireExprIsEqual("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}} * {{1, 2}, {3, 4}}",
                       "{{1472.12, 2208}, {2698.22, 4047}}");
    requireIsEqual("det({{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}})", 0.06);
    requireExprIsEqual("{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012, 1021}, {1022, 1031, 1032}}",
                       "{{111.21, 121.44, 132.73}, {214.62, 226.82, 237.36}}");

}

TEST_CASE("Matrix Scalar Operation Tests", "[matscalar]"){

    SECTION("Matrix Scalar Addition"){
        requireExprIsEqual("{{1, 2}, {3, 4}} + 2", "{{3, 4}, {5, 6}}");
        requireExprIsEqual("2 + {{1, 2}, {3, 4}}", "{{3, 4}, {5, 6}}");
        requireExprIsEqual("2i + {{1, 2}, {3, 4}}", "{{1+2i, 2+2i}, {3+2i, 4+2i}}");
    }
    SECTION("Matrix Scalar Subtraction"){
        requireExprIsEqual("{{1, 2}, {3, 4}} - 2", "{{-1, 0}, {1, 2}}");
        requireExprIsEqual("2 - {{1, 2}, {3, 4}}", "{{1, 0}, {-1, -2}}");
        requireExprIsEqual("2 - {{1, 2i}, {3, 4i}}", "{{1, 2-2i}, {-1, 2-4i}}");
    }
    SECTION("Matrix Scalar Multiplication"){
        requireExprIsEqual("{{1, 2}, {3, 4}} * 2", "{{2, 4}, {6, 8}}");
        requireExprIsEqual("2 * {{1, 2}, {3, 4}}", "{{2, 4}, {6, 8}}");
        requireExprIsEqual("{{i, 2}, {3i, 4}} * 2i", "{{-2, 4i}, {-6, 8i}}");
    }
    SECTION("Matrix Scalar Division"){
        requireExprIsEqual("{{1, 2}, {3, 4}} / 2", "{{0.5, 1}, {1.5, 2}}");
        requireExprIsEqual("2 / {{1, 2}, {3, 4}}", "{{2, 1}, {2.0/3.0, 0.5}}");
    }

}

TEST_CASE("Matrix Transpose Tests", "[transpose]"){

    SECTION("Real Matrix Transpose Tests"){
        requireExprIsEqual("{{1, 2}, {3, 4}}^T", "{{1, 3}, {2, 4}}");
        requireExprIsEqual("{{1, 2, 3}, {4, 5, 6}}^T", "{{1, 4}, {2, 5}, {3, 6}}");
    }

    SECTION("Complex Matrix Transpose Tests"){
        requireExprIsEqual("{{1+2i, 2-5i}, {3, 4}}^T", "{{1+2i, 3}, {2-5i, 4}}");
        requireExprIsEqual("{{1, 2, 3i}, {4, 5, 6}}^T", "{{1, 4}, {2, 5}, {3i, 6}}");
    }

}

TEST_CASE("Matrix Inverse Tests", "[inverse]"){

    SECTION("Real Matrix Inverse Tests"){
        requireExprIsEqual("{{1, 2}, {3, 4}}^-1", "{{-2, 1}, {1.5, -0.5}}");
        requireExprIsEqual("{{10, -9, -12}, {7, -12, 11}, {-10, 10, 3}}^-1",
                        "{{-146./319, -93./319, -243./319}, {-131./319, -90./319, -194./319}, {-50./319, -10./319, -57./319}}");
    }

    SECTION("Complex Matrix Inverse Tests"){
        requireExprIsEqual("{{1i, 2}, {3, 4i}}^-1", "{{-0.4i, 0.2}, {0.3, -0.1i}}");
        requireExprIsEqual("{{10, -9i, -12}, {7, -12, 11i}, {-10i, 10, 3}}^-1",
                           "{{0.0568283247+0.0698351186i, 0.0796074604-0.0530825327i, 0.0326773457-0.012553547i},"
                           " {-0.0646285282+0.0248281262i, 0.0116912281+0.0955086199i, 0.0916841601+0.0564446685i},"
                           " {-0.0173553014+0.1066673283i, 0.1379710152-0.053003865i, 0.0695646228-0.0792244093i}}");
    }

}
