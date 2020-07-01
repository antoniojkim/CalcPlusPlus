
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

{includes}
#include "AbstractFunction.h"
#include "Functions.h"

using namespace std;
using namespace Function;

const Function::AbstractFunction* functions[Functions::numFunctions] = {
    {functions}
};

namespace Functions {
    const Function::AbstractFunction* getFunction(const char* name){
        return functions[Functions::indexOf(name)];
    }
    const Function::AbstractFunction* getFunction(const int index){
        return functions[index];
    }
}
