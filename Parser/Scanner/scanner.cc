
#include "scanner.h"
#include <sstream>

using namespace std;

map<string, Type> keywordType = {
	{"true", TRUE_},
	{"false", FALSE_},
	{"none", NONE_},
	{"NULL", NULL_}
};
map<Type, string> keywordLexeme = {
	{TRUE_, "TRUE"},
	{FALSE_, "FALSE"},
	{NONE_, "NONE"},
	{NULL_, "NULL"}
};
map<string, Type> tokenType = {
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
	{"BOF", BOF_},
	{"EOF", EOF_}
};
map<Type, string> typeLexeme = {
	{LPAREN, "LPAREN"},
	{RPAREN, "RPAREN"},
	{LSQUARE, "LSQUARE"},
	{RSQUARE, "RSQUARE"},
	{LBRACE, "LBRACE"},
	{RBRACE, "RBRACE"},
	{EQUALS, "EQUALS"},
	{PLUS, "PLUS"},
	{MINUS, "MINUS"},
	{STAR, "STAR"},
	{SLASH, "SLASH"},
	{PCT, "PCT"},
	{CARET, "CARET"},
	{AMP, "AMP"},
	{PIPE, "PIPE"},
	{TILDE, "TILDE"},
	{EXCL, "EXCL"},
	{CARET_PIPE, "CARET_PIPE"},
	{STAR_STAR, "STAR_STAR"},
	{SLASH_SLASH, "SLASH_SLASH"},
	{LT_LT, "LT_LT"},
	{GT_GT, "GT_GT"},
	{L_ARROW, "L_ARROW"},
	{R_ARROW, "R_ARROW"},
	{COLON_EQUALS, "COLON_EQUALS"},
	{DOT, "DOT"},
	{COMMA, "COMMA"},
	{COLON, "COLON"},
	{SEMICOLON, "SEMICOLON"},
	{QUESTION, "QUESTION"},
	{POUND, "POUND"},
	{DOLLAR, "DOLLAR"},
	{QUOTE, "QUOTE"},
	{APOSTROPHE, "APOSTROPHE"},
	{BACKSLASH, "BACKSLASH"},
	{BACKTICK, "BACKTICK"},
	{UNDERSCORE, "UNDERSCORE"},
	{BOF_, "BOF_"},
	{EOF_, "EOF_"}
};
map<char, Type> charType = {
	{'(', LPAREN},
	{')', RPAREN},
	{'[', LSQUARE},
	{']', RSQUARE},
	{'{', LBRACE},
	{'}', RBRACE},
	{'=', EQUALS},
	{'+', PLUS},
	{'-', MINUS},
	{'*', STAR},
	{'/', SLASH},
	{'%', PCT},
	{'^', CARET},
	{'&', AMP},
	{'|', PIPE},
	{'~', TILDE},
	{'!', EXCL},
	{'.', DOT},
	{',', COMMA},
	{':', COLON},
	{';', SEMICOLON},
	{'?', QUESTION},
	{'#', POUND},
	{'$', DOLLAR},
	{'\"', QUOTE},
	{'\'', APOSTROPHE},
	{'`', BACKTICK},
	{'_', UNDERSCORE}
};

Type getType(char c) {
    if ('0' <= c && c <= '9')  return NUM;
    if ('a' <= c && c <= 'z')  return ID;
    if ('A' <= c && c <= 'Z')  return ID;
    if (charType.count(c) > 0) return charType[c];

    switch(c){
        case ' ':
            return WHITESPACE;
        case '\t':
            return WHITESPACE;
        case '\n':
            return WHITESPACE;
        case '\r':
            return WHITESPACE;
        default:
            return NONE;
    }
}

std::string getTypeString(const Type& type) {
    if (keywordLexeme.count(type) > 0) return keywordLexeme[type];
    if (typeLexeme.count(type) > 0)    return typeLexeme[type];
    if (type == ID)                    return "ID";
    if (type == STR)                   return "STR";
    if (type == NUM)                   return "NUM";
    if (type == WHITESPACE)            return "WHITESPACE";

    return "NONE";
}

void scan(const std::string& str, std::list<Token>& tokens) {
    istringstream iss{str};
    scan(iss, tokens);
}

void scan(std::istream& in, std::list<Token>& tokens) {
    char c;
    ostringstream token;
    bool openQuote = false;
    Type current = NONE;
    while (in.get(c)) {
        Type type = getType(c);
        // cout << token.str() << " " << getTypeString(current) << "    " << c << " " << getTypeString(type) << endl;
        if (current == NONE || current == type) {
            current = type;
        } else if ((current == ID && (type == NUM || type == UNDERSCORE)) ||
                   (current == UNDERSCORE && (type == ID || type == NUM))) {
            current = ID;
        } else if ((current == NUM && type == DOT) ||
                   (current == NUM && type == ID && (c == 'e' || c == 'E'))) {
            current = NUM;
        } else if (openQuote &&
                    ((current == STR && type == ID) ||
                     (current == NUM && type == ID) ||
                     (current == ID && type == WHITESPACE) ||
                     (current == STR && type == WHITESPACE))) {
            current = STR;

        
        } else if (current == CARET && type == PIPE) { /*  ^|  */
            current = CARET_PIPE;
        } else if (current == STAR && type == STAR) { /*  **  */
            current = STAR_STAR;
        } else if (current == SLASH && type == SLASH) { /*  //  */
            current = SLASH_SLASH;
        } else if (current == COLON && type == EQUALS) { /*  :=  */
            current = COLON_EQUALS;

        } else {
            if (!token.str().empty() && current != WHITESPACE) {
                auto str = token.str();
                if (current == ID && keywordType.count(str) > 0){
                    tokens.emplace_back(Token{str, keywordType[str]});
                } else {
                    tokens.emplace_back(Token{str, current});
                }
                if (current == QUOTE){
                    openQuote = !openQuote;
                }
                token = ostringstream();
            }
            current = type;
        }
        if (current != WHITESPACE){
            token << c;
        }
    }
    if (!token.str().empty()) {
        tokens.emplace_back(Token{token.str(), current});
    }
}



ostream& print(ostream& out, list<Token> tokens, const string& delimiter, const bool& printType) {
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
