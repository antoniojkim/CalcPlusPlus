
#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "parsetree.h"

#define INCLUDE_TRANSITIONS

class Parser {

#ifndef INCLUDE_TRANSITIONS
    std::unordered_map<std::string, bool> terminals;
    std::unordered_map<std::string, bool> nonterminals;
    std::string startSymbol;
    std::vector<std::list<std::string>> rules;
    int numStates;
    std::unordered_map<int, std::unordered_map<std::string, std::pair<bool, int>>> transitions;

  public:
    Parser(const std::string& lr1Path);

#else
  public:
    Parser();

#endif // INCLUDE_TRANSITIONS


    std::unique_ptr<ParseTree> parse(const std::string& input, const bool& showTokens=false);
    std::unique_ptr<ParseTree> parse(std::list<Scanner::Token>& tokens);

    friend std::ostream& operator<<(std::ostream& out, Parser& parser);
};

#endif  // __PARSER_H__