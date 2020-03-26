
#pragma once

#include <iostream>
#include <list>
#include <string>

namespace Scanner {

	enum Type {
		HEX, BIN, NUM, ID, SPECIALID, COMMA, EQUALS, COLON_EQUALS, L_ARROW, PIPE_PIPE,
		AMP_AMP, PIPE, CARET_PIPE, AMP, EQUALS_EQUALS, NOT_EQUALS, LT, GT, LT_EQ, GT_EQ,
		TILDE, LT_LT, GT_GT, PLUS, MINUS, STAR, SLASH, PCT, SLASH_SLASH, EXCL, CARET,
		STAR_STAR, R_ARROW, COLON, LPAREN, RPAREN, LSQUARE, RSQUARE, LBRACE, RBRACE,
		DOT, SEMICOLON, QUESTION, POUND, DOLLAR, QUOTE, APOSTROPHE, BACKSLASH, BACKTICK,
		UNDERSCORE, C, P
	};

	constexpr int numTokens = 52;
	static const std::string typeStrings[numTokens] = {
		"HEX", "BIN", "NUM", "ID", "SPECIALID", "COMMA", "EQUALS", "COLON_EQUALS",
		"L_ARROW", "PIPE_PIPE", "AMP_AMP", "PIPE", "CARET_PIPE", "AMP", "EQUALS_EQUALS",
		"NOT_EQUALS", "LT", "GT", "LT_EQ", "GT_EQ", "TILDE", "LT_LT", "GT_GT", "PLUS",
		"MINUS", "STAR", "SLASH", "PCT", "SLASH_SLASH", "EXCL", "CARET", "STAR_STAR",
		"R_ARROW", "COLON", "LPAREN", "RPAREN", "LSQUARE", "RSQUARE", "LBRACE",
		"RBRACE", "DOT", "SEMICOLON", "QUESTION", "POUND", "DOLLAR", "QUOTE",
		"APOSTROPHE", "BACKSLASH", "BACKTICK", "UNDERSCORE", "C", "P"
	};

	struct Token {
		std::string lexeme;
		Type type;
	};

	bool scan(const std::string& str, std::list<Token>& tokens);

	std::ostream& print(std::ostream& out, std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);
	std::string join(std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);

}

