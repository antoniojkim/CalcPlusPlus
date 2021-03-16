#include <iostream>

#include "../Utils/Exception.h"
#include "../Utils/Status.h"
#include "GreekLetters.h"
#include "Scanner.h"

using namespace std;
using namespace calcpp;
using namespace calcpp::Token;

namespace calcpp {
    namespace Token {
        static const char* const KindStrings[] = {
            // begin sourcegen kindStrings
            "NONE",
            "EMPTY",
            "NUM",
            "COMPLEX",
            "HEX",
            "BIN",
            "ID",
            "CALL",
            "INF",
            "GREEK",
            "LPAREN",
            "RPAREN",
            "LBRACE",
            "RBRACE",
            "LCURLY",
            "RCURLY",
            "QUOTE",
            "STRING",
            "BACKTICK",
            "HASH",
            "BACKSLASH",
            "AMP",
            "AMP_AMP",
            "APOSTROPHE",
            "AT",
            "CARET",
            "CARET_EQUALS",
            "CARET_PIPE",
            "COLON",
            "COLON_COLON",
            "COLON_EQUALS",
            "COMMA",
            "DOLLAR",
            "DOT",
            "DOT_DOT",
            "ELLIPSIS",
            "EQUALS",
            "EQUALS_EQUALS",
            "EXCL",
            "EXCL_EQUALS",
            "EXCL_EXCL",
            "GT",
            "GT_EQUALS",
            "GT_GT",
            "GT_GT_EQUALS",
            "LT",
            "LT_EQUALS",
            "LT_LT",
            "LT_LT_EQUALS",
            "L_ARROW",
            "MINUS",
            "MINUS_EQUALS",
            "PCT",
            "PCT_EQUALS",
            "PIPE",
            "PIPE_PIPE",
            "PLUS",
            "PLUS_EQUALS",
            "QUESTION",
            "R_ARROW",
            "SEMICOLON",
            "SEMICOLON_SEMICOLON",
            "SLASH",
            "SLASH_EQUALS",
            "SLASH_SLASH",
            "STAR",
            "STAR_EQUALS",
            "STAR_STAR",
            "TILDE",
            "TILDE_EQUALS"
            // end sourcegen
        };

        Class::Class(const char* c_str, size_t size, Kind kind) :
            data{.str = {c_str, size}}, kind{kind} {}
        Class::Class(Double value, Kind kind) : data{.value = value}, kind{kind} {}
        Class::Class(unsigned long long ull, Kind kind) :
            data{.ull = ull}, kind{kind} {}

        std::string_view Class::view() const {
            switch (kind) {
                case NUM:
                case COMPLEX:
                case HEX:
                case BIN:
                    THROW_ERROR("Cannot get string view from numeric token");
                default:
                    return std::string_view(data.str.c_str, data.str.size);
            }
        }
        const char* Class::c_str() const {
            switch (kind) {
                case NUM:
                case COMPLEX:
                case HEX:
                case BIN:
                    THROW_ERROR("Cannot get const char* from numeric token");
                default:
                    return data.str.c_str;
            }
        }
        Double Class::value() const {
            switch (kind) {
                case NUM:
                case COMPLEX:
                    return data.value;
                default:
                    THROW_ERROR("Cannot get value from non-numeric token");
            }
        }
        unsigned long long Class::ull() const {
            switch (kind) {
                case HEX:
                case BIN:
                    return data.ull;
                default:
                    THROW_ERROR("Cannot get value from non-numeric token");
            }
        }

        bool operator==(const Class& token, const Kind kind) {
            return token.kind == kind;
        }

        std::ostream& operator<<(std::ostream& out, const Kind kind) {
            return out << KindStrings[(int) kind];
        }

    }  // namespace Token

    bool isPreImplicit(const Kind kind) {
        switch (kind) {
            case NUM:
            case RPAREN:
            case RBRACE:
            case RCURLY:
                return true;
            default:
                return false;
        }
    }

    bool isPostImplicit(const Kind kind) {
        switch (kind) {
            case NUM:
            case LPAREN:
            case LBRACE:
            case LCURLY:
            case ID:
            case GREEK:
                return true;
            default:
                return false;
        }
    }

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
            tokens.emplace_back(TokenClass{c, size, ID});
            return Status::OK();
        }

        const char c1 = c[index + 1];
        if (isalnum(c1) || c1 == '_') { return DFA_id(tokens, c, size, index + 1); }

        tokens.emplace_back(TokenClass{c, index + 1, ID});
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
        tokens.emplace_back(TokenClass{c + 1, i - 1, STRING});
        return DFA_start(tokens, c + i + 1, size - i - 1);
    }

#define APPEND_SYMBOL(index, kind)                                                     \
    tokens.emplace_back(TokenClass{c, index, kind});                                   \
    return DFA_start(tokens, c + index, size - index)

    const std::string inf =
        // begin sourcegen inf
        "\u221E"
        // end sourcegen
        ;

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
                    if (c2 == '.') { APPEND_SYMBOL(3, ELLIPSIS); }
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
                if (std::string_view(c, 3) == inf) { APPEND_SYMBOL(3, INF); }

                const char letter[3] = {c[0], c1, '\0'};
                if (getGreekLetterIndex(letter) != -1) { APPEND_SYMBOL(2, GREEK); }

                THROW_INVALID_SYNTAX_ERROR(c, 0);
        }
    }

    Status DFA_num(TokenCollection& tokens, const char* c, const size_t size) {
        char* end;
        size_t s;

        const char c1 = c[1];
        if (*c == '0') {
            if (size == 1) {
                tokens.emplace_back(TokenClass{(Double) 0, NUM});
                return Status::OK();
            }

            if (c1 == 'x' || c1 == 'X') {
                unsigned long long ull = strtoull(c, &end, 16);
                s = end - c;
                if (s == 1) { THROW_INVALID_SYNTAX_ERROR(c, s + 1); }
                if (s < size && c[s] == '.') { THROW_INVALID_SYNTAX_ERROR(c, s); }
                tokens.emplace_back(TokenClass{ull, HEX});
                return DFA_start(tokens, c + s, size - s);
            }
            if (c1 == 'b' || c1 == 'B') {
                unsigned long long ull = strtoull(c + 2, &end, 2);
                s = end - c;
                if (s == 0) { THROW_INVALID_SYNTAX_ERROR(c, 2); }
                if (s < size && c[s] == '.') { THROW_INVALID_SYNTAX_ERROR(c, s); }
                tokens.emplace_back(TokenClass{ull, BIN});
                return DFA_start(tokens, c + s, size - s);
            }
        } else if (*c == '.' && c1 == '.') {
            return DFA_symbol(tokens, c, size);
        }
        if (isalpha(c1)) { return DFA_id(tokens, c, size, 1); }

        Double value = strtold(c, &end);
        s = end - c;
        if (s < size) {
            const char cs = c[s];
            if (cs == 'i' || cs == 'j') {
                tokens.emplace_back(TokenClass{value, COMPLEX});
                return DFA_start(tokens, c + s + 1, size - s - 1);
            } else if (cs == '.') {
                THROW_INVALID_SYNTAX_ERROR(c, s);
            } else if (s + 1 < size && cs == 'e' && c[s + 1] == '-') {
                THROW_INVALID_SYNTAX_ERROR(c, s);
            }
        }
        tokens.emplace_back(TokenClass{value, NUM});
        return DFA_start(tokens, c + s, size - s);
    }

    Status DFA_start(TokenCollection& tokens, const char* c, const size_t size) {
        if (size == 0) { return Status::OK(); }
        if (isspace(*c)) { return DFA_start(tokens, c + 1, size - 1); }
        if (isalpha(*c) || *c == '_') { return DFA_id(tokens, c, size, 0); }
        if (isdigit(*c)) { return DFA_num(tokens, c, size); }
        if (*c == '.') { return DFA_num(tokens, c, size); }
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
