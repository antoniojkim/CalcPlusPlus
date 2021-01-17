#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <iostream>
#include <list>
#include <string>

namespace Scanner {

	enum Type {
		{types}
	};

	constexpr int numTokens = {numTokens};
	static const std::string typeStrings[numTokens] = {
		{typeStrings}
	};

	struct Token {
		std::string lexeme;
		Type type;
		~Token();
	};

	bool isPreImplicit(Type type);
	bool isPostImplicit(Type type);

	bool scan(const std::string& str, std::list<Token>& tokens);

	std::ostream& print(std::ostream& out, std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);
	std::string join(std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);

}
