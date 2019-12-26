
#include "../../MathEngine/MathEngine.h"

#include <cassert>

using namespace std;

int main(){
    MathEngine engine;

    for (int i = 0; i < 10000; ++i){
        auto tree = engine.parse("cossinh3+5i-arcsin(x, 4)+6integral(sinx, 4, 5)^|4+0x3aF");

        // assert(join(tokens, " ") == "cos sinh 3 + 5i - arcsin ( x , 4 ) + 6 integral ( sin x , 4 , 5 ) ^| 4 + 0x3aF");
    }
}
