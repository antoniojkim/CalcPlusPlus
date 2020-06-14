
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

{includes}
#include "AbstractFunction.h"
#include "FunctionDispatch.h"

using namespace std;
using namespace Function;

const AbstractFunction* functions[Functions::numFunctions] = {
    {functions}
};

const AbstractFunction* getFunction(const char* name){
    return functions[Functions::indexOf(name)];
}
const AbstractFunction* getFunction(const int index){
    return functions[index];
}
