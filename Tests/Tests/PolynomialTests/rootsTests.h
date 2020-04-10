#include "../EngineTest.h"

#include <vector>

#include <Catch2>

TEST_CASE("Quadratic Roots Function Evaluation Tests", "[quad]") {

    SECTION("`quad` Test 1"){
        requireIsEqual("quad(-0.59, -0.47, -1.3)", std::vector<double>());
    }

    SECTION("`quad` Test 2"){
        requireIsEqual("quad(40.5769, -20.7662, 2.6569)", std::vector<double>{0.2558869663, 0.2558869741});
    }

    SECTION("`quad` Test 3"){
        requireIsEqual("quad(-4.89, -2.99, 2.94)", std::vector<double>{-1.1392098425, 0.5277578998});
    }

    SECTION("`quad` Test 4"){
        requireIsEqual("quad(4.01, 6.32, 8.94)", std::vector<double>());
    }

    SECTION("`quad` Test 5"){
        requireIsEqual("quad(0.3844, -9.8208, 62.7264)", std::vector<double>{12.7741935484, 12.7741935484});
    }

    SECTION("`quad` Test 6"){
        requireIsEqual("quad(2.03, -6.35, 3.96)", std::vector<double>{0.8601357534, 2.2679430644});
    }

    SECTION("`quad` Test 7"){
        requireIsEqual("quad(7.44, -4.27, 3.21)", std::vector<double>());
    }

    SECTION("`quad` Test 8"){
        requireIsEqual("quad(-4.22, -9.3, -7.63)", std::vector<double>());
    }

    SECTION("`quad` Test 9"){
        requireIsEqual("quad(6.65, -5.27, 9.36)", std::vector<double>());
    }

    SECTION("`quad` Test 10"){
        requireIsEqual("quad(4.09, -3.92, -8.4)", std::vector<double>{-1.0318877011, 1.990322909});
    }

}
