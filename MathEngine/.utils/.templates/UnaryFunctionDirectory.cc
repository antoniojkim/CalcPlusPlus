
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "UnaryFunctionDirectory.h"
#include "UnaryFunctions/TrigFunctions.h"
#include "UnaryFunctions/ExpLogFunctions.h"

using namespace std;

const UnaryFunction unaryFunctions[numFunctions] = {
    {unaryFunctions}
};

UnaryFunction get_unary_function(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function(index);
}
UnaryFunction get_unary_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", functionNames[functionIndex]);
    }
    return unaryFunctions[functionIndex];
}