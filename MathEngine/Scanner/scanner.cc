
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <cctype>
#include <sstream>

#include "scanner.h"
#include "../Utils/BinarySearch.h"
#include "../Utils/Exception.h"
#include "../Expressions/VariableExpressions/GreekLetters.h"

using namespace std;
using namespace Scanner;


namespace Lexeme {
	constexpr int numLexemes = 49;
	constexpr const char* lexemes[numLexemes] = {
		"!", "!!", "!=", "#", "$", "%", "&", "&&", "'", "(", ")", "*", "**", "+", ",", "-",
		"->", ".", "...", "/", "//", ":", ":=", ";", "<", "<-", "<<", "<=", "=", "==", ">",
		">=", ">>", "?", "C", "P", "[", "\"", "\\", "]", "^", "^|", "_", "`", "{", "|", "||",
		"}", "~"
	};
	constexpr const Type types[numLexemes] = {
		EXCL, EXCL_EXCL, NOT_EQUALS, POUND, DOLLAR, PCT, AMP, AMP_AMP, APOSTROPHE, LPAREN,
		RPAREN, STAR, STAR_STAR, PLUS, COMMA, MINUS, R_ARROW, DOT, ELLIPSIS, SLASH, SLASH_SLASH,
		COLON, COLON_EQUALS, SEMICOLON, LT, L_ARROW, LT_LT, LT_EQ, EQUALS, EQUALS_EQUALS, GT,
		GT_EQ, GT_GT, QUESTION, CHOOSE, PERMUTE, LSQUARE, QUOTE, BACKSLASH, RSQUARE, CARET,
		CARET_PIPE, UNDERSCORE, BACKTICK, LBRACE, PIPE, PIPE_PIPE, RBRACE, TILDE
	};
	constexpr int longestLexeme = 3;

    BINARY_SEARCH_INDEX_OF(lexemes, numLexemes)
}

bool Scanner::isPreImplicit(Type type){
    switch(type){
        case NUM:
        case RPAREN:
        case RSQUARE:
        case RBRACE:
        // case ID:
        case SPECIALID:
            return true;
        default:
            return false;
    }
}

bool Scanner::isPostImplicit(Type type){
    switch(type){
        case NUM:
        case LPAREN:
        case LSQUARE:
        case LBRACE:
        case ID:
        case SPECIALID:
        // case FUNCTION:
            return true;
        default:
            return false;
    }
}

static bool startsWithLexeme(const char* str, size_t size, int& lexemeIndex){
    if (size > 0){
        char substr[Lexeme::longestLexeme+1];
        int lastIndex = -1;
        for (unsigned int i = 0; i < Lexeme::longestLexeme; ++i){
            substr[i] = str[i];
            substr[i+1] = '\0';
            int index = Lexeme::indexOf(substr);
            if (index != -1){
                lastIndex = index;
            }
            if (lastIndex != -1 && (i+1 >= size || i+1 >= Lexeme::longestLexeme)){
                lexemeIndex = lastIndex;
                return true;
            }
        }
    }
    return false;
}

static bool startsWithHex(const char* str, size_t size, int& index){
    if (size > 2 && str[0] == '0' && str[1] == 'x'){
        for (size_t i = 2; i < size; ++i){
            if (!isxdigit(str[i])){
                if (i == 2) return false;
                index = i;
                return true;
            }
        }
        index = size;
        return true;
    }
    return false;
}

static bool startsWithBin(const char* str, size_t size, int& index){
    if (size > 2 && str[0] == '0' && str[1] == 'b'){
        for (unsigned int i = 2; i < size; ++i){
            if (str[i] != '0' && str[i] != '1'){
                if (i == 2) return false;
                index = i;
                return true;
            }
        }
        index = size;
        return true;
    }
    return false;
}

static bool startsWithNum(const char* str, size_t size, int& index){
    if (size > 0){
        int decimalIndex = -1;
        int eIndex = -1;
        for (unsigned int i = 0; i < size; ++i){
            if (!isdigit(str[i])){
                switch(str[i]){
                    case '.':
                        if (decimalIndex == -1){
                            decimalIndex = i;
                            break;
                        }
                        return false;
                    case 'E':
                    case 'e':
                        if (eIndex == -1 && i+1 < size &&
                            ((isdigit(str[i+1]))
                             || (str[i+1] == '-' && i+2 < size && isdigit(str[i+2])))){
                            eIndex = i;
                            break;
                        }
                        return false;
                    case '-':
                        if (eIndex != -1 && eIndex+1 == (int) i){
                            break;
                        }
                        if (i > 0){
                            index = i;
                            return true;
                        }
                        return false;
                    case 'i':
                    case 'j':
                        if (i+1 >= size || !isalpha(str[i+1])){
                            index = i+1;
                            return true;
                        }
                    default:
                        if (i > 0){
                            index = i;
                            return true;
                        }
                        return false;
                }
            }
        }
        if (decimalIndex != -1 && !(decimalIndex > 0 || decimalIndex+1 < (int) size)){
            return false;
        }
        index = size;
        return true;
    }
    return false;
}

static bool startsWithID(const char* str, size_t size, int& index){
    if (size > 0 && isalpha(str[0])){
        for (unsigned int i = 1; i < size; ++i){
            if (!(isalpha(str[i]) || str[i] == '_' || isdigit(str[i]))){
                index = i;
                return true;
            }
        }
        index = size;
        return true;
    }
    return false;
}

static bool startsWithGreekLetter(const char* str, size_t size, int& index){
    if (size > 1){
        std::string letter {str, str+greekLetterLength};
        if (getGreekLetterIndex(letter) != -1){
            index = greekLetterLength;
            return true;
        }
    }
    return false;
}

static bool startsWithWhitespace(const char* str, size_t size, int& index){
    if (size > 0){
        for (unsigned int i = 0; i < size; ++i){
            if (!isspace(str[i])){
                if (i == 0) return false;
                index = i;
                return true;
            }
        }
        index = size;
        return true;
    }
    return false;
}

bool Scanner::scan(const std::string& str, std::list<Token>& tokens) {
    unsigned int i = 0;
    const char* c_str;
    size_t size;
    int index;
    while (i < str.size()){
        c_str = str.c_str() + i;
        size = str.size() - i;
        if (startsWithWhitespace(c_str, size, index)){
            i += index;
        }
        else if (startsWithHex(c_str, size, index)){
            tokens.emplace_back(Token{str.substr(i, index), HEX});
            i += index;
        }
        else if (startsWithBin(c_str, size, index)){
            tokens.emplace_back(Token{str.substr(i, index), BIN});
            i += index;
        }
        else if (startsWithNum(c_str, size, index)){
            tokens.emplace_back(Token{str.substr(i, index), NUM});
            i += index;
        }
        else if (startsWithID(c_str, size, index)){
            if (std::strncmp(c_str, "None", index) == 0 || std::strncmp(c_str, "null", index) == 0){
                tokens.emplace_back(Token{"None", NONE});
            }
            else{
                tokens.emplace_back(Token{str.substr(i, index), ID});
            }
            i += index;
        }
        else if (startsWithLexeme(c_str, size, index)){
            tokens.emplace_back(Token{Lexeme::lexemes[index], Lexeme::types[index]});
            i += strlen(Lexeme::lexemes[index]);
        }
        else if (startsWithGreekLetter(c_str, size, index)){
            tokens.emplace_back(Token{str.substr(i, index), SPECIALID});
            i += index;
        }
        else{
            return false;
        }
    }
    return true;
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
