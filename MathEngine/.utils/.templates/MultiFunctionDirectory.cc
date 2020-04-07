
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "MultiFunctionDirectory.h"
#include "MultiFunctions/ExpLogFunctions.h"

using namespace std;

const MultiFunction multiFunctions[numFunctions] = {
    {multiFunctions}
};

MultiFunction get_multi_function(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Multi Function: ", name);
    }
    return get_multi_function(index);
}
MultiFunction get_multi_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] < 1 && functionNumArgs[functionIndex] != -1){
        throw Exception("Function is not Multi Arg: ", functionNames[functionIndex]);
    }
    return multiFunctions[functionIndex];
}