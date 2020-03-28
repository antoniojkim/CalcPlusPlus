#pragma once

#include <map>

#include "../Scanner/scanner.h"

static const int precedences[Scanner::numTokens] = {
    0, 0, 0, 0, 0, -1, 2, 2, 2, -3, -4, -5, -6, -7, -8, -8, -9, -9, -9, -9, -9, -10,
	-10, -11, -11, -12, -12, -12, -12, -12, 13, 13, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

inline bool isOperator(Scanner::Type type){ return precedences[int(type)] != 0; }
inline bool getPrecedence(Scanner::Type type){ return precedences[int(type)] > 0 ? precedences[int(type)] : -precedences[int(type)]; }
inline bool isRightAssociative(Scanner::Type type){ return precedences[int(type)] > 0; }
