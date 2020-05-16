
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_TILDE, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_EXCL, f_EXCL_EXCL, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_COMMA,
	f_EQUALS, f_COLON_EQUALS, f_L_ARROW, f_R_ARROW, f_PIPE_PIPE, f_AMP_AMP, f_PIPE,
	f_CARET_PIPE, f_AMP, f_EQUALS_EQUALS, f_NOT_EQUALS, f_LT, f_GT, f_LT_EQ, f_GT_EQ,
	nullptr, f_LT_LT, f_GT_GT, f_PLUS, f_MINUS, f_STAR, f_SLASH, f_PCT, f_SLASH_SLASH,
	nullptr, nullptr, f_CHOOSE, f_PERMUTE, f_CARET, f_STAR_STAR, f_COLON, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fe_R_ARROW, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	fe_PLUS, fe_MINUS, fe_STAR, fe_SLASH, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, fe_CARET, fe_STAR_STAR, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	fprime_PLUS, fprime_MINUS, fprime_STAR, fprime_SLASH, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, fprime_CARET, fprime_STAR_STAR, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr
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
