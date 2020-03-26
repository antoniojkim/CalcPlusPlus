#pragma once

#include <map>

#include "../Scanner/scanner.h"

static const int precedences[Scanner::numTokens] = {
    {precedences}
};

inline bool isOperator(Scanner::Type type){ return precedences[int(type)] != 0; }
inline bool getPrecedence(Scanner::Type type){ return precedences[int(type)] > 0 ? precedences[int(type)] : -precedences[int(type)]; }
inline bool isRightAssociative(Scanner::Type type){ return precedences[int(type)] > 0; }
