#include <iostream>

#include "../Utils/Exception.h"
#include "../Utils/Status.h"
#include "Scanner.h"

using namespace calcpp;
using namespace std;

namespace calcpp {
    std::string_view Token::view() const { return std::string_view(c_str, size); }
}  // namespace calcpp

namespace {
    /*
     Rough estimate for number of tokens
     Will always be greater than or equal to the actual number of tokens
    */
    int estimateNumTokens(const std::string& equation) {
        const char* c = equation.c_str();
        const char* end = c + equation.size();
        int numTokens = 0;
        while (c != end) {
            if (isspace(*c)) {
                ++c;
                continue;
            }
            if (isalpha(*c)) {
                ++numTokens;
                while ((++c) != end && isalpha(*c)) {}
            } else if (isdigit(*c)) {
                ++numTokens;
                while ((++c) != end && isdigit(*c)) {}
            } else if (*c == '"') {
                ++numTokens;
                while ((++c) != end && *c != '"') {}
            } else if (*c == '\'') {
                ++numTokens;
                while ((++c) != end && *c != '\'') {}
            } else {
                ++c;
                ++numTokens;
            }
        }
        return numTokens;
    }

    Status DFA_start(TokenCollection& tokens, const char* c, const size_t size);

    Status DFA_id(
        TokenCollection& tokens, const char* c, const size_t size, const size_t index) {
        if (index + 1 == size) {
            tokens.emplace_back(Token{c, size, Token::Kind::ID});
            return Status::OK();
        }

        const char c1 = c[index + 1];
        if (isalnum(c1) || c1 == '_') { return DFA_id(tokens, c, size, index + 1); }

        tokens.emplace_back(Token{c, index + 1, Token::Kind::ID});
        return DFA_start(tokens, c + index + 1, size - index - 1);
    }

    Status DFA_string(TokenCollection& tokens, const char* c, const size_t size) {
        if (size <= 1) { THROW_ERROR("SyntaxError: Standalone quote"); }
        const char c0 = c[0];
        size_t i = 1;
        while (c[i] != c0) {
            if (c[i] == '\\') { ++i; }
            ++i;
            if (i >= size) {
                THROW_ERROR("SyntaxError: EOL while scanning string literal");
            }
        }
        tokens.emplace_back(Token{c + 1, i - 1, Token::Kind::STRING});
        return DFA_start(tokens, c + i + 1, size - i - 1);
    }

#define APPEND_SYMBOL(index, kind)                                                     \
    tokens.emplace_back(Token{c, index, Token::Kind::kind});                           \
    return DFA_start(tokens, c + index, size - index)

    Status DFA_symbol(TokenCollection& tokens, const char* c, const size_t size) {
        const char c1 = (size > 1) ? c[1] : '\0';
        const char c2 = (size > 2) ? c[2] : '\0';
        switch (c[0]) {
            case '(':
                APPEND_SYMBOL(1, LPAREN);
            case ')':
                APPEND_SYMBOL(1, RPAREN);
            case '[':
                APPEND_SYMBOL(1, LBRACE);
            case ']':
                APPEND_SYMBOL(1, RBRACE);
            case '{':
                APPEND_SYMBOL(1, LCURLY);
            case '}':
                APPEND_SYMBOL(1, RCURLY);
            case '+':
                if (c1 == '=') { APPEND_SYMBOL(2, PLUS_EQUALS); }
                APPEND_SYMBOL(1, PLUS);
            case '-':
                if (c1 == '=') { APPEND_SYMBOL(2, MINUS_EQUALS); }
                if (c1 == '>') { APPEND_SYMBOL(2, R_ARROW); }
                APPEND_SYMBOL(1, MINUS);
            case '*':
                if (c1 == '*') { APPEND_SYMBOL(2, STAR_STAR); }
                if (c1 == '=') { APPEND_SYMBOL(2, STAR_EQUALS); }
                APPEND_SYMBOL(1, STAR);
            case '/':
                if (c1 == '/') { APPEND_SYMBOL(2, SLASH_SLASH); }
                if (c1 == '=') { APPEND_SYMBOL(2, SLASH_EQUALS); }
                APPEND_SYMBOL(1, SLASH);
            case '%':
                if (c1 == '=') { APPEND_SYMBOL(2, PCT_EQUALS); }
                APPEND_SYMBOL(1, PCT);
            case '^':
                if (c1 == '=') { APPEND_SYMBOL(2, CARET_EQUALS); }
                if (c1 == '|') { APPEND_SYMBOL(2, CARET_PIPE); }
                APPEND_SYMBOL(1, CARET);
            case '|':
                if (c1 == '|') { APPEND_SYMBOL(2, PIPE_PIPE); }
                APPEND_SYMBOL(1, PIPE);
            case '&':
                if (c1 == '&') { APPEND_SYMBOL(2, AMP_AMP); }
                APPEND_SYMBOL(1, AMP);
            case '=':
                if (c1 == '=') { APPEND_SYMBOL(2, EQUALS_EQUALS); }
                APPEND_SYMBOL(1, EQUALS);
            case ':':
                if (c1 == '=') { APPEND_SYMBOL(2, COLON_EQUALS); }
                if (c1 == ':') { APPEND_SYMBOL(2, COLON_COLON); }
                APPEND_SYMBOL(1, COLON);
            case ';':
                if (c1 == ';') { APPEND_SYMBOL(2, SEMICOLON_SEMICOLON); }
                APPEND_SYMBOL(1, SEMICOLON);
            case '<':
                if (c1 == '=') { APPEND_SYMBOL(2, LT_EQUALS); }
                if (c1 == '-') { APPEND_SYMBOL(2, L_ARROW); }
                if (c1 == '<') {
                    if (c2 == '=') { APPEND_SYMBOL(3, LT_LT_EQUALS); }
                    APPEND_SYMBOL(2, LT_LT);
                }
                APPEND_SYMBOL(1, LT);
            case '>':
                if (c1 == '=') { APPEND_SYMBOL(2, GT_EQUALS); }
                if (c1 == '>') {
                    if (c2 == '=') { APPEND_SYMBOL(3, GT_GT_EQUALS); }
                    APPEND_SYMBOL(2, GT_GT);
                }
                APPEND_SYMBOL(1, GT);
            case '~':
                if (c1 == '=') { APPEND_SYMBOL(2, TILDE_EQUALS); }
                APPEND_SYMBOL(1, TILDE);
            case '!':
                if (c1 == '=') { APPEND_SYMBOL(2, EXCL_EQUALS); }
                if (c1 == '!') { APPEND_SYMBOL(2, EXCL_EXCL); }
                APPEND_SYMBOL(1, EXCL);
            case '.':
                if (c1 == '.') {
                    if (c2 == '.') { APPEND_SYMBOL(3, ELLIPSES); }
                    APPEND_SYMBOL(2, DOT_DOT);
                }
                APPEND_SYMBOL(1, DOT);
            case ',':
                APPEND_SYMBOL(1, COMMA);
            case '`':
                APPEND_SYMBOL(1, BACKTICK);
            case '?':
                APPEND_SYMBOL(1, QUESTION);
            case '$':
                APPEND_SYMBOL(1, DOLLAR);
            case '#':
                APPEND_SYMBOL(1, HASH);
            case '@':
                APPEND_SYMBOL(1, AT);
            case '\\':
                if (c1 == '\'') { APPEND_SYMBOL(2, APOSTROPHE); }
                if (c1 == '"') { APPEND_SYMBOL(2, QUOTE); }
                APPEND_SYMBOL(1, BACKSLASH);
            default:
                THROW_INVALID_SYNTAX_ERROR(c, 0);
        }
    }

    Status DFA_bin(
        TokenCollection& tokens, const char* c, const size_t size, const size_t index) {
        if (index + 1 == size) {
            if (index > 1) {
                tokens.emplace_back(Token{c, size, Token::Kind::BIN});
                return Status::OK();
            }
            THROW_INVALID_SYNTAX_ERROR(c, index);
        }

        switch (c[index + 1]) {
            case '0':
            case '1':
                return DFA_bin(tokens, c, size, index + 1);
            case '.':
                THROW_INVALID_SYNTAX_ERROR(c, index + 1);
            default:
                break;
        }

        tokens.emplace_back(Token{c, index + 1, Token::Kind::BIN});
        return DFA_start(tokens, c + index + 1, size - index - 1);
    }

    Status DFA_hex(
        TokenCollection& tokens, const char* c, const size_t size, const size_t index) {
        if (index + 1 == size) {
            if (index > 1) {
                tokens.emplace_back(Token{c, size, Token::Kind::HEX});
                return Status::OK();
            }
            THROW_INVALID_SYNTAX_ERROR(c, index);
        }

        const char c1 = c[index + 1];
        if (isxdigit(c1)) { return DFA_hex(tokens, c, size, index + 1); }
        if (index == 1) { THROW_INVALID_SYNTAX_ERROR(c, index + 1); }
        switch (c1) {
            case '.':
                THROW_INVALID_SYNTAX_ERROR(c, index + 1);
            default:
                break;
        }

        tokens.emplace_back(Token{c, index + 1, Token::Kind::HEX});
        return DFA_start(tokens, c + index + 1, size - index - 1);
    }

    Status DFA_num(
        TokenCollection& tokens,
        const char* c,
        const size_t size,
        const size_t index,
        bool dec = false,
        bool exp = false) {
        // cout << "Entering DFA_num(size: " << size << ", index: " << index << ")"
        //      << endl;
        if (index + 1 == size) {
            tokens.emplace_back(Token{c, size, Token::Kind::NUM});
            return Status::OK();
        }
        const char c1 = c[index + 1];
        if (isdigit(c1)) { return DFA_num(tokens, c, size, index + 1, dec, exp); }
        const char c0 = c[index];
        if (c0 == '.') { return DFA_symbol(tokens, c, size); }
        if (index == 0 && c0 == '0') {
            if (c1 == 'x' || c1 == 'X') { return DFA_hex(tokens, c, size, index + 1); }
            if (c1 == 'b' || c1 == 'B') { return DFA_bin(tokens, c, size, index + 1); }
        }
        switch (c1) {
            case '.':
                if (dec || exp) { THROW_INVALID_SYNTAX_ERROR(c, index + 1); }
                return DFA_num(tokens, c, size, index + 1, true, exp);
            case '-':
                if (exp && (c0 == 'e' || c0 == 'E')) {
                    return DFA_num(tokens, c, size, index + 1, dec, exp);
                }
                THROW_INVALID_SYNTAX_ERROR(c, index);
            case 'e':
            case 'E':
                if (!exp) { return DFA_num(tokens, c, size, index + 1, dec, true); }
                THROW_INVALID_SYNTAX_ERROR(c, index + 1);
            case 'i':
            case 'j':
                tokens.emplace_back(Token{c, index + 1, Token::Kind::COMPLEX});
                return DFA_start(tokens, c + index + 2, size - index - 2);
            default:
                break;
        }
        if (isalpha(c1)) { return DFA_id(tokens, c, size, index + 1); }

        tokens.emplace_back(Token{c, index + 1, Token::Kind::NUM});
        return DFA_start(tokens, c + index + 1, size - index - 1);
    }

    Status DFA_start(TokenCollection& tokens, const char* c, const size_t size) {
        if (size == 0) { return Status::OK(); }
        if (isspace(*c)) { return DFA_start(tokens, c + 1, size - 1); }
        if (isalpha(*c) || *c == '_') { return DFA_id(tokens, c, size, 0); }
        if (isdigit(*c)) { return DFA_num(tokens, c, size, 0); }
        if (*c == '.') { return DFA_num(tokens, c, size, 0, true); }
        if (*c == '\'' || *c == '"') { return DFA_string(tokens, c, size); }
        return DFA_symbol(tokens, c, size);
    }

}  // namespace

namespace calcpp {

    TokenCollection scan(const std::string& equation) {
        TokenCollection tokens;
        tokens.reserve(estimateNumTokens(equation));

        Status status = DFA_start(tokens, equation.c_str(), equation.size());
        if (status.ok()) { return tokens; }

        THROW_ERROR("Failed to scan: " << equation);
    }

}  // namespace calcpp
