
#include <cstring>
#include <sstream>
#include <regex>
#include <unordered_map>

#include "scanner.h"

using namespace std;
using namespace Scanner;

constexpr int numLexemes = 47;
static const std::string lexemes[numLexemes] = {
	":=", "<-", "||", "&&", "^|", "==", "!=", "<=", ">=", "<<", ">>", "//", "**",
	"->", "\"", "\'", "\\", ",", "=", "|", "&", "<", ">", "~", "+", "-", "*", "/",
	"%", "!", "^", ":", "(", ")", "[", "]", "{", "}", ".", ";", "?", "#", "$", "`",
	"_", "C", "P"
};
static const Type lexemeTypes[numLexemes] = {
	COLON_EQUALS, L_ARROW, PIPE_PIPE, AMP_AMP, CARET_PIPE, EQUALS_EQUALS,
	NOT_EQUALS, LT_EQ, GT_EQ, LT_LT, GT_GT, SLASH_SLASH, STAR_STAR, R_ARROW, QUOTE,
	APOSTROPHE, BACKSLASH, COMMA, EQUALS, PIPE, AMP, LT, GT, TILDE, PLUS, MINUS,
	STAR, SLASH, PCT, EXCL, CARET, COLON, LPAREN, RPAREN, LSQUARE, RSQUARE, LBRACE,
	RBRACE, DOT, SEMICOLON, QUESTION, POUND, DOLLAR, BACKTICK, UNDERSCORE, C, P
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
static const std::regex HEX_regex ("^(0x[0-9a-fA-F]+)");
static const std::regex BIN_regex ("^(0b[01]+)");
static const std::regex NUM_regex ("^(([0-9]*\\.?[0-9]+(i(?![a-zA-Z]))?))");
static const std::regex ID_regex ("^[a-zA-Z_][0-9a-zA-Z_]+");

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
    
    if (std::regex_search(str, match, HEX_regex)){
        tokens.emplace_back(Token{match[0], HEX});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, BIN_regex)){
        tokens.emplace_back(Token{match[0], BIN});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, NUM_regex)){
        tokens.emplace_back(Token{match[0], NUM});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, ID_regex)){
        tokens.emplace_back(Token{match[0], ID});
        return Scanner::scan(match.suffix(), tokens);
    }
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
