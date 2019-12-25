
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "parsetree.h"

class Parser {
    std::map<std::string, bool> terminals;
    std::map<std::string, bool> nonterminals;
    std::string startSymbol;
    std::vector<std::list<std::string>> rules;
    int numStates;
    std::map<int, std::map<std::string, std::pair<bool, int>>> transitions;

   public:
    Parser(const std::string& lr1Path);

    std::unique_ptr<ParseTree> parse(const std::string& input, const bool& showTokens=false);
    std::unique_ptr<ParseTree> parse(std::list<Scanner::Token>& tokens);

    friend std::ostream& operator<<(std::ostream& out, Parser& parser);
};

#endif  // PARSER_H
