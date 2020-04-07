#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cmath>
#include <cstring>

#include "../../Scanner/scanner.h"

constexpr const char* operators[Scanner::numTokens] = {
    {operators}
};
constexpr const int precedences[Scanner::numTokens] = {
    {precedences}
};
constexpr const bool singleOperators[Scanner::numTokens] = {
    {singleOperators}
};

constexpr const int operatorStart = {operatorStart};
constexpr const int operatorEnd = {operatorEnd};
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
