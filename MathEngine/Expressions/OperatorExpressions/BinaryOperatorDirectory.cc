
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
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, f_COMMA,
	f_EQUALS, f_COLON_EQUALS, f_L_ARROW, f_PIPE_PIPE, f_AMP_AMP, f_PIPE, f_CARET_PIPE,
	f_AMP, f_EQUALS_EQUALS, f_NOT_EQUALS, f_LT, f_GT, f_LT_EQ, f_GT_EQ, nullptr, f_LT_LT,
	f_GT_GT, f_PLUS, f_MINUS, f_STAR, f_SLASH, f_PCT, f_SLASH_SLASH, nullptr, f_CARET,
	f_STAR_STAR, f_R_ARROW, f_COLON, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr
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
