
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/exceptions.h"
#include "Operators.h"
#include "BinaryOperatorDirectory.h"
#include "OperatorDerivatives/OperatorDerivatives.h"
#include "OperatorDirectory/BinaryOperators.h"
#include "OperatorExpressions/Addition.h"
#include "OperatorExpressions/Division.h"
#include "OperatorExpressions/Exponent.h"
#include "OperatorExpressions/Multiplication.h"
#include "OperatorExpressions/RightArrow.h"
#include "OperatorExpressions/Subtraction.h"

using namespace std;
using namespace Scanner;

const BinaryOperator binaryOperators[numTokens] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_COMMA,
	f_EQUALS, f_COLON_EQUALS, f_L_ARROW, f_R_ARROW, f_PIPE_PIPE, f_AMP_AMP, f_PIPE,
	f_CARET_PIPE, f_AMP, f_EQUALS_EQUALS, f_NOT_EQUALS, f_LT, f_GT, f_LT_EQ, f_GT_EQ,
	nullptr, f_LT_LT, f_GT_GT, f_PLUS, f_MINUS, f_STAR, f_SLASH, f_PCT, f_SLASH_SLASH,
	nullptr, nullptr, f_CHOOSE, f_PERMUTE, f_CARET, f_STAR_STAR, f_COLON, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fe_R_ARROW, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	fe_PLUS, fe_MINUS, fe_STAR, fe_SLASH, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, fe_CARET, fe_STAR_STAR, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	fprime_PLUS, fprime_MINUS, fprime_STAR, fprime_SLASH, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fprime_CARET, fprime_STAR_STAR, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
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


// const BinaryOperatorIntegral binaryOperatorIntegrals[numTokens] = {
//     {binaryOperatorIntegrals}
// };

BinaryOperatorIntegral getBinaryOperatorIntegral(const std::string& name) {
    // int index = getOperatorIndex(name);
    // if (index == -1){
    //     throw Exception("Unknown Binary Operator: ", name);
    // }
    // return getBinaryOperatorIntegral(index);
    return nullptr;
}
BinaryOperatorIntegral getBinaryOperatorIntegral(int operatorIndex) {
    // if (operatorIndex < 0 || operatorIndex >= numTokens){
    //     throw Exception("Invalid Operator Index: ", operatorIndex);
    // }
    // return binaryOperatorIntegrals[operatorIndex];
    return nullptr;
}


const BinaryOperatorSimplify binaryOperatorSimplifys[numTokens] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr
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
