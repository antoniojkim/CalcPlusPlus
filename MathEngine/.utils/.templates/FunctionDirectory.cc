
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "Functions.h"
#include "MultiFunctions/Basic.h"
#include "MultiFunctions/Calculus.h"
#include "MultiFunctions/ExpLogFunctions.h"
#include "MultiFunctions/SpecialFunctions.h"
#include "MultiFunctions/Statistics.h"
#include "MultiFunctionExprs/fft.h"
#include "MultiFunctionExprs/polynomial.h"
#include "MultiFunctionExprs/tuple.h"
#include "UnaryFunctions/BasicFunctions.h"
#include "UnaryFunctions/ExpLogFunctions.h"
#include "UnaryFunctions/SpecialFunctions.h"
#include "UnaryFunctions/TrigFunctions.h"
#include "UnaryFunctionExprs/basic.h"
#include "UnaryFunctionExprs/linalg.h"

using namespace std;

/***************************************************
 ***************** Unary Functions *****************
 ***************************************************/

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


/***************************************************
 ************** Unary Function Exprs ***************
 ***************************************************/

const UnaryFunctionExpr unaryFunctionExprs[numFunctions] = {
    {unaryFunctionExprs}
};

UnaryFunctionExpr get_unary_function_expr(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_unary_function_expr(index);
}
UnaryFunctionExpr get_unary_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] != 1){
        throw Exception("Function is not Unary: ", functionNames[functionIndex]);
    }
    return unaryFunctionExprs[functionIndex];
}


/***************************************************
 ***************** Multi Functions *****************
 ***************************************************/

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


/***************************************************
 *************** Multi Expr Functions **************
 ***************************************************/

const MultiFunctionExpr multiFunctionExprs[numFunctions] = {
    {multiFunctionExprs}
};

MultiFunctionExpr get_multi_function_expr(const string& name){
    int index = getFunctionIndex(name);
    if (index == -1){
        throw Exception("Unknown Multi Function: ", name);
    }
    return get_multi_function_expr(index);
}
MultiFunctionExpr get_multi_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    if (functionNumArgs[functionIndex] < 1 && functionNumArgs[functionIndex] != -1){
        throw Exception("Function is not Multi Arg: ", functionNames[functionIndex]);
    }
    return multiFunctionExprs[functionIndex];
}
