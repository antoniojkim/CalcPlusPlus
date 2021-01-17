
#include "../../MathEngine/MathEngine.h"
#include "../utils.h"

#include <cassert>

using namespace std;

MathEngine engine;

double time_parse(const std::string& equation){
    auto expr = engine.parse(equation);
    auto evald = expr->eval();
    return evald->value();
}

int main(){
    const string equation = "cos(sinh 3)+5i-arcsin(x, 4)+6integral(sin(x), 4, 5)^|4+0x3aF";

    timeit(10000, time_parse, equation);

}
