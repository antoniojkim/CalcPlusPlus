
#include "scanner.h"
#include <sstream>
#include <regex>
#include <unordered_map>

using namespace std;
using namespace Scanner;

const unordered_map<string, Type> tokenType = {
    {"x", X},
    {"y", Y},
    {"(", LPAREN},
    {")", RPAREN},
    {"[", LSQUARE},
    {"]", RSQUARE},
    {"{", LBRACE},
    {"}", RBRACE},
    {"=", EQUALS},
    {"+", PLUS},
    {"-", MINUS},
    {"*", STAR},
    {"/", SLASH},
    {"%", PCT},
    {"^", CARET},
    {"&", AMP},
    {"|", PIPE},
    {"~", TILDE},
    {"!", EXCL},
    {"^|", CARET_PIPE},
    {"**", STAR_STAR},
    {"//", SLASH_SLASH},
    {"<<", LT_LT},
    {">>", GT_GT},
    {"<-", L_ARROW},
    {"->", R_ARROW},
    {":=", COLON_EQUALS},
    {".", DOT},
    {",", COMMA},
    {":", COLON},
    {";", SEMICOLON},
    {"?", QUESTION},
    {"#", POUND},
    {"$", DOLLAR},
    {"\"", QUOTE},
    {"'", APOSTROPHE},
    {"\\", BACKSLASH},
    {"`", BACKTICK},
    {"_", UNDERSCORE},
    {"C", C},
    {"P", P},
    {"BOF", BOF_},
    {"EOF", EOF_}
};

const std::regex whitespace_regex("^\\s+");
const std::regex hex_regex("^(0x[0-9a-fA-f]+)");
const std::regex bin_regex("^(0b[01]+)");
const std::regex num_regex("^((\\d*\\.?\\d+(i(?![a-zA-Z]))?))");
const std::regex id_regex("^((a(rc)?)?(sin|cos|tan|csc|sec|cot)h?|(fr|to)(bin|two|hex)|rand(int|q)?|log(2|ab)?|norm(inv)?|(sm)?fib|l(n2?|p)|integral|floor2?|riemann|stndv_?|spread|prime|gamma|elasd|exprv|heron|var_?|ceil|mean|cosl|kurt|skew|corr|dist|prod|abs|deg|det|erf|exp|neg|rad|avg|gcd|geo|lcm|max|min|mdn|IQR|sum)");
const std::regex token_regex("^BOF|EOF|\\^\\||\\*\\*|//|<<|>>|<-|->|:=|\\\"|\\\\|x|y|\\(|\\)|\\[|\\]|\\{|\\}|=|\\+|-|\\*|/|%|\\^|&|\\||~|!|\\.|,|:|;|\\?|#|\\$|'|`|_|C|P");

bool Scanner::scan(const std::string& str, std::list<Token>& tokens) {
    if (str.empty()) return true;

    std::smatch match;
    if (std::regex_search(str, match, whitespace_regex)){
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, hex_regex)){
        tokens.emplace_back(Token{match[0], NUM});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, bin_regex)){
        tokens.emplace_back(Token{match[0], NUM});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, num_regex)){
        tokens.emplace_back(Token{match[0], NUM});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, id_regex)){
        tokens.emplace_back(Token{match[0], ID});
        return Scanner::scan(match.suffix(), tokens);
    }
    if (std::regex_search(str, match, token_regex)){
        tokens.emplace_back(Token{match[0], tokenType.at(match[0])});
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
