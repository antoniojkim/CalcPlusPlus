

using namespace std;

#include <Catch2>
#include "../EngineTest.h"

TEST_CASE("Basic Factorial Tests", "[factorial]" ) {

    requireIsEqual("5!", 120);
    requireIsEqual("5.5!", 287.88527781504436);
    requireIsEqual("gamma(6.5)", 287.88527781504436);
    requireIsEqual("(-5.5)!", -0.0600196013005);
    requireIsEqual("170!", 7.257415615307999e306);
    requireIsEqual("171!", GSL_POSINF);
    requireIsEqual("lnfact(171)", 711.71472580229);
    requireIsEqual("lnfact(400)", 2000.500697983241389);

}

TEST_CASE("Basic Double Factorial Tests", "[double_factorial]" ) {

    requireIsEqual("10!!", 3840);
    requireIsEqual("297!!", 1.2552756225993e304);
    requireIsEqual("298!!", GSL_POSINF);
    requireIsEqual("lndfact(298)", 703.2884004587592792);
    requireIsEqual("lndfact(600)", 1622.85000411305158137);

}

TEST_CASE("Basic Combinatorics Tests", "[combinatorics]" ) {

    SECTION("Choose"){
        // requireIsEqual("10C5", 252);
        requireIsEqual("C(10, 5)", 252);
        // requireIsEqual("170C25", 5.81369626545789772e29);
        requireIsEqual("C(170, 25)", 5.81369626545789772e29);
        // requireIsEqual("171C25", 6.809192201323976e29);
        requireIsEqual("C(171, 25)", 6.809192201323976e29);
        requireIsEqual("choose(171, 25)", 6.809192201323976e29);
        requireIsEqual("lnchoose(171, 25)", 68.693241190470369412);
    }

    SECTION("Permute"){
        // requireIsEqual("10P5", 30240);
        requireIsEqual("P(10, 5)", 30240);
        // requireIsEqual("171P25", 1.05618810460147483e55);
        requireIsEqual("P(171, 25)", 1.05618810460147483e55);
        requireIsEqual("permute(171, 25)", 1.05618810460147483e55);
        requireIsEqual("lnpermute(171, 25)", 126.69684641345088935);
    }

}
