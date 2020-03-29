
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "Operators.h"
#include "BinaryOperatorDirectory.h"
#include "OperatorDirectory/BinaryOperators.h"

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