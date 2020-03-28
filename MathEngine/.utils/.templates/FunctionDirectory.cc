#include "FunctionDirectory.h"
#include "../../Utils/exceptions.h"

#include <cmath>
#include <gsl/gsl_math.h>
#include <unordered_map>

using namespace std;

const std::string functionNames[numFunctions] = {
    {functionNames}
};
static const int functionNumArgs[numFunctions] = {
    {functionNumArgs}
};

int getFunctionIndex(const std::string& name){
    for (int i = 0; i < numFunctions; ++i){
        if (name == functionNames[i]){
            return i;
        }
    }
    return -1;
}
int getFunctionNumArgs(const std::string& name){
    return getFunctionNumArgs(getFunctionIndex(name));
}
int getFunctionNumArgs(int index){
    if (index >= 0 && index < numFunctions){
        return functionNumArgs[index];
    }
    return 0;
}

UnaryFunction get_unary_function(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    if (functionNumArgs[index] != 1){
        throw Exception("Function is not Unary: ", name);
    }

    throw Exception("Unimplemented Error: get_unary_function");
}