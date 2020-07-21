#include "../EngineTest.h"

#include <vector>

#include <Catch2>

TEST_CASE("Quadratic Roots Function Evaluation Tests", "[quad]") {

    SECTION("`quad` Test 1"){
        requireExprIsEqual("quad(-0.59, -0.47, -1.3)", "()");
    }

    SECTION("`quad` Test 2"){
        requireExprIsEqual("quad(40.5769, -20.7662, 2.6569)", "(x1 = 0.2558869663, x2 = 0.2558869741)");
    }

    SECTION("`quad` Test 3"){
        requireExprIsEqual("quad(-4.89, -2.99, 2.94)", "(x1 = -1.1392098425, x2 = 0.5277578998)");
    }

    SECTION("`quad` Test 4"){
        requireExprIsEqual("quad(4.01, 6.32, 8.94)", "()");
    }

    SECTION("`quad` Test 5"){
        requireExprIsEqual("quad(0.3844, -9.8208, 62.7264)", "(x1 = 12.7741935483871,)");
    }

    SECTION("`quad` Test 6"){
        requireExprIsEqual("quad(2.03, -6.35, 3.96)", "(x1 = 0.8601357534, x2 = 2.2679430644)");
    }

    SECTION("`quad` Test 7"){
        requireExprIsEqual("quad(7.44, -4.27, 3.21)", "()");
    }

    SECTION("`quad` Test 8"){
        requireExprIsEqual("quad(-4.22, -9.3, -7.63)", "()");
    }

    SECTION("`quad` Test 9"){
        requireExprIsEqual("quad(6.65, -5.27, 9.36)", "()");
    }

    SECTION("`quad` Test 10"){
        requireExprIsEqual("quad(4.09, -3.92, -8.4)", "(x1 = -1.0318877011, x2 = 1.990322909)");
    }

}

TEST_CASE("Complex Quadratic Roots Function Evaluation Tests", "[quadc]") {

    SECTION("`quadc` Test 1"){
        requireExprIsEqual("quadc(7.13, 6.37, -5.62)", "(z1 = -1.4405668937, z2 = 0.547158759)");
    }

    SECTION("`quadc` Test 2"){
        requireExprIsEqual("quadc(6.57, -0.53, 9.01)", "(z1 = 0.0403348554-1.1703666875i, z2 = 0.0403348554+1.1703666875i)");
    }

    SECTION("`quadc` Test 3"){
        requireExprIsEqual("quadc(-7.08, 5.46, 8.04)", "(z1 = -0.7476655109, z2 = 1.5188519516)");
    }

    SECTION("`quadc` Test 4"){
        requireExprIsEqual("quadc(-9.79, 3.27, 9.46)", "(z1 = -0.8300803701, z2 = 1.1640946704)");
    }

    SECTION("`quadc` Test 5"){
        requireExprIsEqual("quadc(-4.09, 3.9, -2.55)", "(z1 = 0.4767726161-0.6294122299i, z2 = 0.4767726161+0.6294122299i)");
    }

    SECTION("`quadc` Test 6"){
        requireExprIsEqual("quadc(3.77, -1.81, 0.59)", "(z1 = 0.2400530504-0.3144411022i, z2 = 0.2400530504+0.3144411022i)");
    }

    SECTION("`quadc` Test 7"){
        requireExprIsEqual("quadc(-0.29, -2.0, 6.78)", "(z1 = -9.387123963, z2 = 2.4905722388)");
    }

    SECTION("`quadc` Test 8"){
        requireExprIsEqual("quadc(-9.13, -6.09, 7.32)", "(z1 = -1.2890185284, z2 = 0.6219867649)");
    }

    SECTION("`quadc` Test 9"){
        requireExprIsEqual("quadc(8.7, -2.59, 5.87)", "(z1 = 0.1488505747-0.8078094764i, z2 = 0.1488505747+0.8078094764i)");
    }

    SECTION("`quadc` Test 10"){
        requireExprIsEqual("quadc(-3.19, -4.9, 6.95)", "(z1 = -2.4319198787, z2 = 0.895869722)");
    }

}

TEST_CASE("Cubic Root Function Evaluation Test", "[cubic]"){

    SECTION("`cubic` Test 1"){
        requireExprIsEqual("cubic(-5.86, 8.97, -3.8, 4.45)", "(x1 = 1.4455355285,)");
    }

    SECTION("`cubic` Test 2"){
        requireExprIsEqual("cubic(-2.59, 3.17, 9.24, -4.77)", "(x1 = -1.6387848792, x2 = 0.4696047611, x3 = 2.3931183421)");
    }

    SECTION("`cubic` Test 3"){
        requireExprIsEqual("cubic(-1.46, 9.96, -1.31, -3.86)", "(x1 = -0.5413746444, x2 = 0.7369970403, x3 = 6.6262954123)");
    }

    SECTION("`cubic` Test 4"){
        requireExprIsEqual("cubic(2.35, 4.19, 6.4, -4.07)", "(x1 = 0.4609066714,)");
    }

    SECTION("`cubic` Test 5"){
        requireExprIsEqual("cubic(5.21, -2.29, -9.48, 2.94)", "(x1 = -1.2977023907, x2 = 0.3032385272, x3 = 1.4340032109)");
    }

    SECTION("`cubic` Test 6"){
        requireExprIsEqual("cubic(4.23, 6.54, -8.69, -3.48)", "(x1 = -2.2870720625, x2 = -0.334478549, x3 = 1.0754513207)");
    }

    SECTION("`cubic` Test 7"){
        requireExprIsEqual("cubic(-1.39, -1.44, 9.85, 0.02)", "(x1 = -3.2291079174, x2 = -0.0020298557, x3 = 2.1951665501)");
    }

    SECTION("`cubic` Test 8"){
        requireExprIsEqual("cubic(3.97, -5.2, -3.22, -6.34)", "(x1 = 2.0728094429,)");
    }

    SECTION("`cubic` Test 9"){
        requireExprIsEqual("cubic(-2.44, -9.2, 2.63, 9.1)", "(x1 = -3.795594644, x2 = -0.9787841347, x3 = 1.0038869754)");
    }

    SECTION("`cubic` All Same Root Test"){
        requireExprIsEqual("cubic(1, -3, 3, -1)", "(x1 = 1, x2 = 1, x3 = 1)");
    }

}

TEST_CASE("Complex Cubic Root Function Evaluation Test", "[cubicc]"){

    SECTION("`cubicc` Test 1"){
        requireExprIsEqual("cubicc(8.32, 0.33, 3.04, -3.24)", "(z1 = -0.2986260682-0.7805306619i, z2 = -0.2986260682+0.7805306619i, z3 = 0.5575886749)");
    }

    SECTION("`cubicc` Test 2"){
        requireExprIsEqual("cubicc(7.68, -5.64, -5.4, 2.83)", "(z1 = -0.7780463051, z2 = 0.4427688832, z3 = 1.069652422)");
    }

    SECTION("`cubicc` Test 3"){
        requireExprIsEqual("cubicc(8.59, 5.2, 8.51, 7.52)", "(z1 = -0.7780981196, z2 = 0.0863715278-1.0571839249i, z3 = 0.0863715278+1.0571839249i)");
    }

    SECTION("`cubicc` Test 4"){
        requireExprIsEqual("cubicc(5.15, 4.42, 9.01, -6.32)", "(z1 = -0.681036649-1.4042594493i, z2 = -0.681036649+1.4042594493i, z3 = 0.5038208707)");
    }

    SECTION("`cubicc` Test 5"){
        requireExprIsEqual("cubicc(-1.62, -6.42, -6.82, -9.43)", "(z1 = -3.2167798679, z2 = -0.3730915476-1.292428908i, z3 = -0.3730915476+1.292428908i)");
    }

    SECTION("`cubicc` Test 6"){
        requireExprIsEqual("cubicc(9.66, -1.63, -3.49, 1.76)", "(z1 = -0.7069170893, z2 = 0.4378270747-0.2569799433i, z3 = 0.4378270747+0.2569799433i)");
    }

    SECTION("`cubicc` Test 7"){
        requireExprIsEqual("cubicc(-8.69, -4.77, 0.32, 8.58)", "(z1 = -0.7007444772-0.8167115336i, z2 = -0.7007444772+0.8167115336i, z3 = 0.852582165)");
    }

    SECTION("`cubicc` Test 8"){
        requireExprIsEqual("cubicc(-7.39, -0.92, -3.56, 1.52)", "(z1 = -0.225678005-0.760482276i, z2 = -0.225678005+0.760482276i, z3 = 0.3268634525)");
    }

    SECTION("`cubicc` Test 9"){
        requireExprIsEqual("cubicc(-0.55, 9.8, -3.39, 0.9)", "(z1 = 0.1737182117-0.2519624024i, z2 = 0.1737182117+0.2519624024i, z3 = 17.4707453948)");
    }

    SECTION("`cubicc` Test 10"){
        requireExprIsEqual("cubicc(3.44, -0.95, -0.52, -4.11)", "(z1 = -0.4683761127-0.8750210665i, z2 = -0.4683761127+0.8750210665i, z3 = 1.212915016)");
    }

}
