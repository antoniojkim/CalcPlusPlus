#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cmath>
#include <cstring>

#include "../Scanner/scanner.h"

namespace Operators {
    constexpr const int size = 34;
    constexpr const int offset = 28;
    constexpr const char* operators[size] = {
        ",", "=", ":=", "<-", "->", "...", "||", "&&", "|", "^|", "&", "==", "!=", "<", ">",
		"<=", ">=", "~", "'", "<<", ">>", "+", "-", "*", "/", "%", "//", "!", "!!", "C", "P",
		"^", "**", ":"
    };
    constexpr const int precedences[size] = {
        -1, 2, 2, 2, 2, -3, -4, -5, -6, -7, -8, -9, -9, -10, -10, -10, -10, 10, -11, -12, -12,
		-13, -13, -14, -14, -14, -14, -14, -14, -14, -14, 15, 15, 16
    };
    constexpr const bool singleOperators[size] = {
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 0
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
    constexpr bool isOperator(Scanner::Type type){ return (int(type) - offset) >= 0; }
    constexpr int getPrecedence(Scanner::Type type){ return std::abs(precedences[int(type) - offset]); }
    constexpr bool isRightAssociative(Scanner::Type type){ return precedences[int(type) - offset] > 0; }
    constexpr bool isSingleOperator(Scanner::Type type){ return singleOperators[int(type) - offset]; }
}
