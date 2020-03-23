#ifndef __TRANSITIONS_H__
#define __TRANSITIONS_H__

#include <array>
#include <list>
#include <map>
#include <string>
#include <utility>

#include "../Scanner/scanner.h"

enum Terminal: int {
    AMP, APOSTROPHE, BACKSLASH, BACKTICK, BOF_, C, CARET, CARET_PIPE, COLON,
	COLON_EQUALS, COMMA, DOLLAR, DOT, EOF_, EQUALS, EXCL, FALSE_, GT_GT, HEX, ID,
	LBRACE, LPAREN, LSQUARE, LT_LT, L_ARROW, MINUS, NONE_, NULL_, NUM, P, PCT, PIPE,
	PLUS, POUND, QUESTION, QUOTE, RBRACE, RPAREN, RSQUARE, R_ARROW, SEMICOLON,
	SLASH, SLASH_SLASH, STAR, STAR_STAR, STR, TILDE, TRUE_, UNDERSCORE, X, Y
};
constexpr int numTerminals = 51;

enum NonTerminal: int {
    start = -16, arglist, expr, expr1, expr11, expr12, expr13, expr3, expr4, expr5,
	expr6, expr7, exprn, factor, lvalue, statement
};
constexpr int numNonTerminals = 16;

std::string getTerminalString(Terminal terminal);
std::string getNonTerminalString(NonTerminal nonterminal);

int convertTokenType(Scanner::Type type);

constexpr int numRules = 48;
constexpr int maxRuleLength = 5+1;
extern const std::array<std::array<int, maxRuleLength>, numRules> rules;

constexpr int numTransitions = 79;
extern const std::vector<std::map<int, int>> transitions;

#endif // __TRANSITIONS_H__