
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include "parsetree.h"

class Parser {
    
   public:
    Parser();

    std::unique_ptr<ParseTree> parse(const std::string& input, const bool& verbose=false);
    std::unique_ptr<ParseTree> parse(std::list<Scanner::Token>& tokens);

    friend std::ostream& operator<<(std::ostream& out, Parser& parser);
};

#endif  // PARSER_H
