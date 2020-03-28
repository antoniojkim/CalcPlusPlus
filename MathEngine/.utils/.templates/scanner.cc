
#include <cstring>
#include <cctype>
#include <sstream>

#include "scanner.h"
#include "../Utils/exceptions.h"
#include "../Expressions/FunctionExpressions/FunctionDirectory.h"

using namespace std;
using namespace Scanner;

constexpr int numLexemes = {numLexemes};
static const std::string lexemes[numLexemes] = {
	{lexemes}
};
static const Type lexemeTypes[numLexemes] = {
	{lexemeTypes}
};

static bool startsWithLexeme(const char* str, size_t size, int& lexemeIndex){
    if (size > 0){
        for (int i = 0; i < numLexemes; ++i){
            if (size >= lexemes[i].size()){
                if (strncmp(str, lexemes[i].c_str(), lexemes[i].size()) == 0){
                    lexemeIndex = i;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool startsWithFunction(const char* str, size_t size, int& index){
    if (size > 0){
        for (int i = 0; i < numFunctions; ++i){
            if (size >= functionNames[i].size()){
                if (strncmp(str, functionNames[i].c_str(), functionNames[i].size()) == 0){
                    index = i;
                    return true;
                }
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
        bool isDecimal = false;
        for (unsigned int i = 0; i < size; ++i){
            if (!isdigit(str[i])){
                if (i == 0) return false;
                switch(str[i]){
                    case '.':
                        if (!isDecimal){
                            isDecimal = true;
                            break;
                        }
                        return false;
                    case 'i':
                        index = (i+1 < size && !isalpha(str[i+1])) ? i+1 : i;
                        return true;
                    default:
                        index = i;
                        return true;
                }   
            }
        }
        index = size;
        return true;
    }
    return false;
}

static bool startsWithID(const char* str, size_t size, int& index){
    if (size > 0 && isalpha(str[0])){
        for (unsigned int i = 1; i < size; ++i){
            if (!(isalnum(str[i]) || str[i] == '_')){
                index = i;
                return true;
            }
        }
        index = size;
        return true;
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
        else if (startsWithLexeme(c_str, size, index)){
            tokens.emplace_back(Token{lexemes[index], lexemeTypes[index]});
            i += lexemes[index].size();
        }
        else if (startsWithFunction(c_str, size, index)){
            tokens.emplace_back(Token{functionNames[index], ID});
            i += functionNames[index].size();
        }
        else if (startsWithID(c_str, size, index)){
            tokens.emplace_back(Token{str.substr(i, index), ID});
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