
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <list>
#include <string>

namespace Scanner {

enum Type {
	ID,
	STR,
	NUM,
	HEX,
	X,
	Y,
	LPAREN,
	RPAREN,
	LSQUARE,
	RSQUARE,
	LBRACE,
	RBRACE,
	EQUALS,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	PCT,
	CARET,
	AMP,
	PIPE,
	TILDE,
	EXCL,
	CARET_PIPE,
	STAR_STAR,
	SLASH_SLASH,
	LT_LT,
	GT_GT,
	L_ARROW,
	R_ARROW,
	COLON_EQUALS,
	DOT,
	COMMA,
	COLON,
	SEMICOLON,
	QUESTION,
	POUND,
	DOLLAR,
	QUOTE,
	APOSTROPHE,
	BACKSLASH,
	BACKTICK,
	UNDERSCORE,
	BOF_,
	EOF_,
	TRUE_,
	FALSE_,
	NONE_,
	NULL_,
	WHITESPACE,
	NONE
};

// extern std::map<std::string, Type> keywordType;
// extern std::map<Type, std::string> keywordLexeme;
// extern std::map<std::string, Type> tokenType;
// extern std::map<Type, std::string> typeLexeme;
// extern std::map<char, Type> charType;

// Type getType(char c);
std::string getTypeString(const Type& type);

struct Token {
    std::string lexeme;
    Type type;
};

bool scan(const std::string& str, std::list<Token>& tokens);
// void scan(std::istream& in, std::list<Token>& tokens);

std::ostream& print(std::ostream& out, std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);
std::string join(std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);

}

#endif
