
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "Operators.h"
#include "OperatorDirectory.h"
#include "OperatorDerivatives/OperatorDerivatives.h"
#include "Operators/BinaryOperators.h"
#include "Operators/UnaryOperators.h"
#include "OperatorExpressions/Addition.h"
#include "OperatorExpressions/Division.h"
#include "OperatorExpressions/Exponent.h"
#include "OperatorExpressions/Multiplication.h"
#include "OperatorExpressions/RightArrow.h"
#include "OperatorExpressions/Subtraction.h"

using namespace std;
using namespace Scanner;

const UnaryOperator unaryOperators[numTokens] = {
    {unaryOperators}
};

UnaryOperator getUnaryOperator(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getUnaryOperator(index);
}
UnaryOperator getUnaryOperator(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return unaryOperators[operatorIndex];
}

const BinaryOperator binaryOperators[numTokens] = {
    {binaryOperators}
};

BinaryOperator getBinaryOperator(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getBinaryOperator(index);
}
BinaryOperator getBinaryOperator(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return binaryOperators[operatorIndex];
}


const OperatorExpr operatorExprs[numTokens] = {
    {operatorExprs}
};

OperatorExpr getOperatorExpr(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getOperatorExpr(index);
}
OperatorExpr getOperatorExpr(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return operatorExprs[operatorIndex];
}


const OperatorDerivative operatorDerivatives[numTokens] = {
    {operatorDerivatives}
};

OperatorDerivative getOperatorDerivative(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getOperatorDerivative(index);
}
OperatorDerivative getOperatorDerivative(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return operatorDerivatives[operatorIndex];
}


// const OperatorIntegral operatorIntegrals[numTokens] = {
//     {operatorIntegrals}
// };

OperatorIntegral getOperatorIntegral(const std::string& name) {
    // int index = getOperatorIndex(name);
    // if (index == -1){
    //     throw Exception("Unknown Binary Operator: ", name);
    // }
    // return getOperatorIntegral(index);
    return nullptr;
}
OperatorIntegral getOperatorIntegral(int operatorIndex) {
    // if (operatorIndex < 0 || operatorIndex >= numTokens){
    //     throw Exception("Invalid Operator Index: ", operatorIndex);
    // }
    // return operatorIntegrals[operatorIndex];
    return nullptr;
}


const OperatorSimplify operatorSimplifys[numTokens] = {
    {operatorSimplifys}
};

OperatorSimplify getOperatorSimplify(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getOperatorSimplify(index);
}
OperatorSimplify getOperatorSimplify(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return operatorSimplifys[operatorIndex];
}
