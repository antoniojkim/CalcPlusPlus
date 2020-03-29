#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cmath>
#include <cstring>

#include "../../Scanner/scanner.h"

constexpr const char* operators[Scanner::numTokens] = {
    "", "", "", "", "", "", ",", "=", ":=", "<-", "||", "&&", "|", "^|", "&", "==",
	"!=", "<", ">", "<=", ">=", "~", "<<", ">>", "+", "-", "*", "/", "%", "//", "!",
	"^", "**", "->", ":", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", ""
};
constexpr const int precedences[Scanner::numTokens] = {
    0, 0, 0, 0, 0, 0, -1, 2, 2, 2, -3, -4, -5, -6, -7, -8, -8, -9, -9, -9, -9, -9,
	-10, -10, -11, -11, -12, -12, -12, -12, -12, 13, 13, 14, 14, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
constexpr const bool singleOperators[Scanner::numTokens] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

constexpr const int operatorStart = 6;
constexpr const int operatorEnd = 34;
constexpr int getOperatorIndex(const char * lexeme){
    for (int i = operatorStart; i <= operatorEnd; ++i){
        if (std::strcmp(lexeme, operators[i]) == 0){
            return i;
        }
    }
    return -1;
}
inline int getOperatorIndex(const std::string& lexeme){
    return getOperatorIndex(lexeme.c_str());
}
constexpr bool isOperator(Scanner::Type type){ return precedences[int(type)] != 0; }
constexpr int getPrecedence(Scanner::Type type){ return std::abs(precedences[int(type)]); }
constexpr bool isRightAssociative(Scanner::Type type){ return precedences[int(type)] > 0; }
constexpr bool isSingleOperator(Scanner::Type type){ return singleOperators[int(type)]; }
