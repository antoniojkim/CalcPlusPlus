
#include <cstring>
#include <sstream>
#include <regex>
#include <unordered_map>

#include "scanner.h"

using namespace std;
using namespace Scanner;

constexpr int numLexemes = {numLexemes};
static const std::string lexemes[numLexemes] = {
	{lexemes}
};
static const Type lexemeTypes[numLexemes] = {
	{lexemeTypes}
};

static bool startsWithLexeme(const std::string& str, int& lexemeIndex){
    if (!str.empty()){
        for (int i = 0; i < numLexemes; ++i){
            if (str.size() >= lexemes[i].size()){
                if (strncmp(str.c_str(), lexemes[i].c_str(), lexemes[i].size()) == 0){
                    lexemeIndex = i;
                    return true;
                }
            }
        }
    }
    return false;
}

static const std::regex whitespace_regex("^\\s+");
{regexes}

bool Scanner::scan(const std::string& str, std::list<Token>& tokens) {
    if (str.empty()) return true;

    std::smatch match;
    if (std::regex_search(str, match, whitespace_regex)){
        return Scanner::scan(match.suffix(), tokens);
    }
    int index;
    if (startsWithLexeme(str, index)){
        tokens.emplace_back(Token{lexemes[index], lexemeTypes[index]});
        return Scanner::scan(str.substr(lexemes[index].size()), tokens);
    }
    {regex_searches}
    return false;
}


ostream& Scanner::print(ostream& out, list<Token> tokens, const string& delimiter, const bool& printType) {
    bool first = true;
    for (auto& token : tokens) {
        if (first) {
            first = false;
        } else {
            out << delimiter;
        }
        out << token.lexeme;
        if (printType){
            out << "  " << typeStrings[token.type];
        }
    }
    return out;
}

string Scanner::join(list<Token> tokens, const string& delimiter, const bool& printType) {
    ostringstream out;
    bool first = true;
    for (auto& token : tokens) {
        if (first) {
            first = false;
        } else {
            out << delimiter;
        }
        if (printType){
            out << "  " << typeStrings[token.type];
        }
        out << token.lexeme;
    }
    return out.str();
}
