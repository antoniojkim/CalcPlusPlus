#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cmath>
#include <cstring>

#include "../Scanner/scanner.h"

namespace Operators {
    constexpr const int size = {numOperators};
    constexpr const int offset = {operatorOffset};
    constexpr const char* operators[size] = {
        {operators}
    };
    constexpr const int precedences[size] = {
        {precedences}
    };
    constexpr const bool singleOperators[size] = {
        {singleOperators}
    };

    constexpr int indexOf(const char * lexeme){
        for (int i = 0; i < size; ++i){
            if (std::strcmp(lexeme, operators[i]) == 0){
                return i;
            }
        }
        return -1;
    }
    inline int indexOf(const std::string& lexeme){
        return indexOf(lexeme.c_str());
    }
    constexpr bool isOperator(int type){ return (int(type) - offset) >= 0; }
    constexpr int getPrecedence(int type){ return std::abs(precedences[int(type) - offset]); }
    constexpr bool isRightAssociative(int type){ return precedences[int(type) - offset] > 0; }
    constexpr bool isSingleOperator(int type){ return singleOperators[int(type) - offset]; }
}
