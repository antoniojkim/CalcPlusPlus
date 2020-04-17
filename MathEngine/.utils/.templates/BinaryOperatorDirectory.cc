
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "Operators.h"
#include "BinaryOperatorDirectory.h"
#include "OperatorDirectory/BinaryOperators.h"
#include "OperatorExpressions/Addition.h"
#include "OperatorExpressions/Division.h"
#include "OperatorExpressions/Multiplication.h"
#include "OperatorExpressions/Subtraction.h"

using namespace std;
using namespace Scanner;

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
    if (binaryOperators[operatorIndex]){
        return binaryOperators[operatorIndex];
    }
    throw Exception("Operator is not Binary: ", operators[operatorIndex]);
}


const BinaryOperatorExpr binaryOperatorExprs[numTokens] = {
    {binaryOperatorExprs}
};

BinaryOperatorExpr getBinaryOperatorExpr(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getBinaryOperatorExpr(index);
}
BinaryOperatorExpr getBinaryOperatorExpr(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return binaryOperatorExprs[operatorIndex];
}


const BinaryOperatorDerivative binaryOperatorDerivatives[numTokens] = {
    {binaryOperatorDerivatives}
};

BinaryOperatorDerivative getBinaryOperatorDerivative(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getBinaryOperatorDerivative(index);
}
BinaryOperatorDerivative getBinaryOperatorDerivative(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return binaryOperatorDerivatives[operatorIndex];
}


const BinaryOperatorIntegral binaryOperatorIntegrals[numTokens] = {
    {binaryOperatorIntegrals}
};

BinaryOperatorIntegral getBinaryOperatorIntegral(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getBinaryOperatorIntegral(index);
}
BinaryOperatorIntegral getBinaryOperatorIntegral(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return binaryOperatorIntegrals[operatorIndex];
}


const BinaryOperatorSimplify binaryOperatorSimplifys[numTokens] = {
    {binaryOperatorSimplifys}
};

BinaryOperatorSimplify getBinaryOperatorSimplify(const std::string& name) {
    int index = getOperatorIndex(name);
    if (index == -1){
        throw Exception("Unknown Binary Operator: ", name);
    }
    return getBinaryOperatorSimplify(index);
}
BinaryOperatorSimplify getBinaryOperatorSimplify(int operatorIndex) {
    if (operatorIndex < 0 || operatorIndex >= numTokens){
        throw Exception("Invalid Operator Index: ", operatorIndex);
    }
    return binaryOperatorSimplifys[operatorIndex];
}
