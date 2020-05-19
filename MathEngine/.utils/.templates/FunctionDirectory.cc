
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "FunctionDirectory.h"
#include "Functions.h"
#include "ExprFunctions/basic.h"
#include "ExprFunctions/calculus.h"
#include "ExprFunctions/fft.h"
#include "ExprFunctions/linalg.h"
#include "ExprFunctions/polynomial.h"
#include "ValueFunctions/BasicFunctions.h"
#include "ValueFunctions/Calculus.h"
#include "ValueFunctions/ExpLogFunctions.h"
#include "ValueFunctions/Random.h"
#include "ValueFunctions/SpecialFunctions.h"
#include "ValueFunctions/Statistics.h"
#include "ValueFunctions/TrigFunctions.h"
#include "DerivativeFunctions/BasicFunctions.h"
#include "DerivativeFunctions/ExpLogFunctions.h"
#include "DerivativeFunctions/TrigFunctions.h"

using namespace std;
using Function::numFunctions;

/***************************************************
 ***************** Unary Functions *****************
 ***************************************************/

const ValueFunction valueFunctions[numFunctions] = {
    {valueFunctions}
};

ValueFunction get_function(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Function: ", name);
    }
    return get_function(index);
}
ValueFunction get_function(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    return valueFunctions[functionIndex];
}


/***************************************************
 ***************** Expr Functions ******************
 ***************************************************/

const ExprFunction exprFunctions[numFunctions] = {
    {exprFunctions}
};

ExprFunction get_function_expr(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Unary Function: ", name);
    }
    return get_function_expr(index);
}
ExprFunction get_function_expr(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    return exprFunctions[functionIndex];
}


/***************************************************
 ************** Function Derivatives ***************
 ***************************************************/

const DerivativeFunction derivativeFunctions[numFunctions] = {
    {derivativeFunctions}
};

DerivativeFunction get_function_derivative(const string& name){
    int index = Function::indexOf(name);
    if (index == -1){
        throw Exception("Unknown Function: ", name);
    }
    return get_function_derivative(index);
}
DerivativeFunction get_function_derivative(int functionIndex){
    if (functionIndex < 0 || functionIndex >= numFunctions){
        throw Exception("Invalid Function Index: ", functionIndex);
    }
    return derivativeFunctions[functionIndex];
}
