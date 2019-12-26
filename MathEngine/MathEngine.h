#ifndef __MATH_ENGINE_H__
#define __MATH_ENGINE_H__

#include <list>
#include <memory>
#include <string>

// #include "Parser/StringUtils.h"
#include "Scanner/scanner.h"
#include "Parser/parser.h"
#include "Utils/exceptions.h"

class MathEngine {

    Parser parser;

    public:
        std::list<Scanner::Token> scan(const std::string& input);

        std::unique_ptr<ParseTree> parse(const std::string& input);
        std::unique_ptr<ParseTree> parse(std::list<Scanner::Token>& tokens);
};

#endif // __MATH_ENGINE_H__
