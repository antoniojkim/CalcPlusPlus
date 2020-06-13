#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <iostream>
#include <list>
#include <string>

namespace Scanner {

	enum Type {
		HEX, BIN, NUM, ID, SPECIALID, FUNCTION, TUPLE, MATRIX, COMMA, EQUALS, COLON_EQUALS,
		L_ARROW, R_ARROW, PIPE_PIPE, AMP_AMP, PIPE, CARET_PIPE, AMP, EQUALS_EQUALS, NOT_EQUALS,
		LT, GT, LT_EQ, GT_EQ, TILDE, APOSTROPHE, LT_LT, GT_GT, PLUS, MINUS, STAR, SLASH, PCT,
		SLASH_SLASH, EXCL, EXCL_EXCL, CHOOSE, PERMUTE, CARET, STAR_STAR, COLON, LPAREN, RPAREN,
		LSQUARE, RSQUARE, LBRACE, RBRACE, DOT, SEMICOLON, QUESTION, POUND, DOLLAR, QUOTE,
		BACKSLASH, BACKTICK, UNDERSCORE
	};

	constexpr int numTokens = 56;
	static const std::string typeStrings[numTokens] = {
		"HEX", "BIN", "NUM", "ID", "SPECIALID", "FUNCTION", "TUPLE", "MATRIX", "COMMA",
		"EQUALS", "COLON_EQUALS", "L_ARROW", "R_ARROW", "PIPE_PIPE", "AMP_AMP", "PIPE",
		"CARET_PIPE", "AMP", "EQUALS_EQUALS", "NOT_EQUALS", "LT", "GT", "LT_EQ", "GT_EQ",
		"TILDE", "APOSTROPHE", "LT_LT", "GT_GT", "PLUS", "MINUS", "STAR", "SLASH", "PCT",
		"SLASH_SLASH", "EXCL", "EXCL_EXCL", "CHOOSE", "PERMUTE", "CARET", "STAR_STAR", "COLON",
		"LPAREN", "RPAREN", "LSQUARE", "RSQUARE", "LBRACE", "RBRACE", "DOT", "SEMICOLON",
		"QUESTION", "POUND", "DOLLAR", "QUOTE", "BACKSLASH", "BACKTICK", "UNDERSCORE"
	};

	struct Token {
		std::string lexeme;
		Type type;
	};

	bool isPreImplicit(Type type);
	bool isPostImplicit(Type type);

	bool scan(const std::string& str, std::list<Token>& tokens);

	std::ostream& print(std::ostream& out, std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);
	std::string join(std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);

}
