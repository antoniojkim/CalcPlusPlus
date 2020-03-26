
#include "scanner.h"
#include <sstream>
#include <regex>
#include <unordered_map>

using namespace std;
using namespace Scanner;

static const unordered_map<string, Type> tokenType = {
	{",", COMMA},
	{"=", EQUALS},
	{":=", COLON_EQUALS},
	{"<-", L_ARROW},
	{"||", PIPE_PIPE},
	{"&&", AMP_AMP},
	{"|", PIPE},
	{"^|", CARET_PIPE},
	{"&", AMP},
	{"==", EQUALS_EQUALS},
	{"!=", NOT_EQUALS},
	{"<", LT},
	{">", GT},
	{"<=", LT_EQ},
	{">=", GT_EQ},
	{"~", TILDE},
	{"<<", LT_LT},
	{">>", GT_GT},
	{"+", PLUS},
	{"-", MINUS},
	{"*", STAR},
	{"/", SLASH},
	{"%", PCT},
	{"//", SLASH_SLASH},
	{"!", EXCL},
	{"^", CARET},
	{"**", STAR_STAR},
	{"->", R_ARROW},
	{":", COLON},
	{"(", LPAREN},
	{")", RPAREN},
	{"[", LSQUARE},
	{"]", RSQUARE},
	{"{", LBRACE},
	{"}", RBRACE},
	{".", DOT},
	{";", SEMICOLON},
	{"?", QUESTION},
	{"#", POUND},
	{"$", DOLLAR},
	{"\"", QUOTE},
	{"\'", APOSTROPHE},
	{"\\", BACKSLASH},
	{"`", BACKTICK},
	{"_", UNDERSCORE},
	{"C", C},
	{"P", P}
};

static const std::regex whitespace_regex("^\\s+");
static const std::regex HEX_regex ("^(0x[0-9a-fA-F]+)");
static const std::regex BIN_regex ("^(0b[01]+)");
static const std::regex NUM_regex ("^(([0-9]*\\.?[0-9]+(i(?![a-zA-Z]))?))");
static const std::regex ID_regex ("^[a-zA-Z_][0-9a-zA-Z_]+");
static const std::regex token_regex("^(,|=|:=|<\\-|\\|\\||&&|\\||\\^\\||&|==|!=|<|>|<=|>=|~|<<|>>|\\+|\\-|\\*|/|%|//|!|\\^|\\*\\*|\\->|:|\\(|\\)|\\[|\\]|\\{|\\}|\\.|;|\\?|#|\\$|\\\"|\\'|\\\\|`|_|C|P)");

bool Scanner::scan(const std::string& str, std::list<Token>& tokens) {
    if (str.empty()) return true;

    std::smatch match;
    if (std::regex_search(str, match, whitespace_regex)){
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, token_regex)){
        tokens.emplace_back(Token{match[0], tokenType.at(match[0])});
        return Scanner::scan(match.suffix(), tokens);
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
