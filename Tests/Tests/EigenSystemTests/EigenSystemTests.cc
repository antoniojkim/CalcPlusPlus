

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Eigen System Tests", "[eigen]" ) {

    requireExprIsEqual("Eig{{1, 0, 0}, {2, -1, 2}, {4, -4, 5}}",
                       "(Λ = {{3}, {1}, {1}}, X = {{0, -0.4082482904638632, 0}, {-0.4472135954999579, 0.4082482904638631, -0.7071067811865474}, {-0.8944271909999159, 0.8164965809277261, -0.7071067811865476}})");

}
