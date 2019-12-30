
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


std::string Scanner::getTypeString(const Type& type) {
    switch(type){
        case ID: return "ID";
        case STR: return "STR";
        case NUM: return "NUM";
        case HEX: return "HEX";
        case X: return "X";
        case Y: return "Y";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LSQUARE: return "LSQUARE";
        case RSQUARE: return "RSQUARE";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case EQUALS: return "EQUALS";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case PCT: return "PCT";
        case CARET: return "CARET";
        case AMP: return "AMP";
        case PIPE: return "PIPE";
        case TILDE: return "TILDE";
        case EXCL: return "EXCL";
        case CARET_PIPE: return "CARET_PIPE";
        case STAR_STAR: return "STAR_STAR";
        case SLASH_SLASH: return "SLASH_SLASH";
        case LT_LT: return "LT_LT";
        case GT_GT: return "GT_GT";
        case L_ARROW: return "L_ARROW";
        case R_ARROW: return "R_ARROW";
        case COLON_EQUALS: return "COLON_EQUALS";
        case DOT: return "DOT";
        case COMMA: return "COMMA";
        case COLON: return "COLON";
        case SEMICOLON: return "SEMICOLON";
        case QUESTION: return "QUESTION";
        case POUND: return "POUND";
        case DOLLAR: return "DOLLAR";
        case QUOTE: return "QUOTE";
        case APOSTROPHE: return "APOSTROPHE";
        case BACKSLASH: return "BACKSLASH";
        case BACKTICK: return "BACKTICK";
        case UNDERSCORE: return "UNDERSCORE";
        case C: return "C";
        case P: return "P";
        case BOF_: return "BOF_";
        case EOF_: return "EOF_";
        case TRUE_: return "TRUE_";
        case FALSE_: return "FALSE_";
        case NONE_: return "NONE_";
        case NULL_: return "NULL_";
        case WHITESPACE: return "WHITESPACE";
        case NONE: return "NONE";
        default: return "NONE";
    }
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
            out << "  " << getTypeString(token.type);
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
            out << "  " << getTypeString(token.type);
        }
        out << token.lexeme;
    }
    return out.str();
}
