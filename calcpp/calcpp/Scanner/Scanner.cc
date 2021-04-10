#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

#include "../Utils/Exception.h"
#include "../Utils/Stream.h"
#include "GreekLetters.h"
#include "Scanner.h"

using namespace std;
using namespace calcpp;
using namespace calcpp::Token;

namespace calcpp {
    namespace Token {
        static const char* const KindStrings[] = {
            // begin sourcegen kindStrings
            "EOF",          "NONE",         "EMPTY",
            "NUM",          "COMPLEX",      "HEX",
            "BIN",          "ID",           "CALL",
            "INF",          "GREEK",        "LPAREN",
            "RPAREN",       "LBRACE",       "RBRACE",
            "LCURLY",       "RCURLY",       "QUOTE",
            "STRING",       "BACKTICK",     "HASH",
            "BACKSLASH",    "AMP",          "AMP_AMP",
            "APOSTROPHE",   "AT",           "CARET",
            "CARET_EQUALS", "CARET_PIPE",   "COLON",
            "COLON_COLON",  "COLON_EQUALS", "COMMA",
            "DOLLAR",       "DOT",          "DOT_DOT",
            "ELLIPSIS",     "EQUALS",       "EQUALS_EQUALS",
            "EXCL",         "EXCL_EQUALS",  "EXCL_EXCL",
            "GT",           "GT_EQUALS",    "GT_GT",
            "GT_GT_EQUALS", "LT",           "LT_EQUALS",
            "LT_LT",        "LT_LT_EQUALS", "L_ARROW",
            "MINUS",        "MINUS_EQUALS", "PCT",
            "PCT_EQUALS",   "PIPE",         "PIPE_PIPE",
            "PLUS",         "PLUS_EQUALS",  "QUESTION",
            "R_ARROW",      "SEMICOLON",    "SEMICOLON_SEMICOLON",
            "SLASH",        "SLASH_EQUALS", "SLASH_SLASH",
            "STAR",         "STAR_EQUALS",  "STAR_STAR",
            "TILDE",        "TILDE_EQUALS"
            // end sourcegen
        };
    }  // namespace Token

    std::ostream& operator<<(std::ostream& out, const Token::Kind kind) {
        return out << Token::KindStrings[(int) kind];
    }

    bool isPreImplicit(const Token::Kind kind) {
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

    bool isPostImplicit(const Token::Kind kind) {
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

    namespace Token {
        struct Contents {
            union {
                double d;
                unsigned long long ull;
                std::string_view str;
            } val;

            Token::Kind kind;

            Contents() : val{0} {}

            void set(const Token::Kind kind, const char* c, const size_t size) {
                this->kind = kind;
                val.str = std::string_view(c, size);
            }
            void set(const Token::Kind kind, const double d) {
                this->kind = kind;
                val.d = d;
            }
            void set(const Token::Kind kind, const unsigned long long ull) {
                this->kind = kind;
                val.ull = ull;
            }
        };
    }  // namespace Token

    namespace DFA {

        struct State {
            const char* c = nullptr;
            const size_t size = 0;
        };  // namespace DFA

        DFA::State start(Token::Contents& token, const char* c, const size_t size);

        DFA::State id(
            Token::Contents& token,
            const char* c,
            const size_t size,
            const size_t index) {
            if (index + 1 == size) {
                token.set(ID, c, size);
                return DFA::State{};
            }

            const char c1 = c[index + 1];
            if (isalnum(c1) || c1 == '_') { return DFA::id(token, c, size, index + 1); }

            token.set(ID, c, index + 1);
            return DFA::State{c + index + 1, size - index - 1};
        }

        DFA::State string(Token::Contents& token, const char* c, const size_t size) {
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
            token.set(STRING, c + 1, i - 1);
            return DFA::State{c + i + 1, size - i - 1};
        }

#define APPEND_SYMBOL(index, kind)                                                     \
    token.set(kind, c, index);                                                         \
    return DFA::State { c + index, size - index }

        const std::string inf =
            // begin sourcegen inf
            "\u221E"
            // end sourcegen
            ;

        DFA::State symbol(Token::Contents& token, const char* c, const size_t size) {
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

        DFA::State num(Token::Contents& token, const char* c, const size_t size) {
            char* end;
            size_t s;

            const char c1 = c[1];
            if (*c == '0') {
                if (size == 1) {
                    token.set(NUM, 0.0);
                    return DFA::State{};
                }

                if (c1 == 'x' || c1 == 'X') {
                    unsigned long long ull = strtoull(c, &end, 16);
                    s = end - c;
                    if (s == 1) { THROW_INVALID_SYNTAX_ERROR(c, s + 1); }
                    if (s < size && c[s] == '.') { THROW_INVALID_SYNTAX_ERROR(c, s); }
                    token.set(HEX, ull);
                    return DFA::State{c + s, size - s};
                }
                if (c1 == 'b' || c1 == 'B') {
                    unsigned long long ull = strtoull(c + 2, &end, 2);
                    s = end - c;
                    if (s == 0) { THROW_INVALID_SYNTAX_ERROR(c, 2); }
                    if (s < size && c[s] == '.') { THROW_INVALID_SYNTAX_ERROR(c, s); }
                    token.set(BIN, ull);
                    return DFA::State{c + s, size - s};
                }
            } else if (*c == '.' && c1 == '.') {
                return DFA::symbol(token, c, size);
            }
            if (isalpha(c1)) { return DFA::id(token, c, size, 1); }

            double value = strtod(c, &end);
            s = end - c;
            if (s < size) {
                const char cs = c[s];
                if (cs == 'i' || cs == 'j') {
                    token.set(COMPLEX, value);
                    return DFA::State{c + s + 1, size - s - 1};
                } else if (cs == '.') {
                    THROW_INVALID_SYNTAX_ERROR(c, s);
                } else if (s + 1 < size && cs == 'e' && c[s + 1] == '-') {
                    THROW_INVALID_SYNTAX_ERROR(c, s);
                }
            }
            token.set(NUM, value);
            return DFA::State{c + s, size - s};
        }

        DFA::State start(Token::Contents& token, const char* c, const size_t size) {
            if (size == 0) { return DFA::State{}; }
            if (isspace(*c)) { return DFA::start(token, c + 1, size - 1); }
            if (isalpha(*c) || *c == '_') { return DFA::id(token, c, size, 0); }
            if (isdigit(*c)) { return DFA::num(token, c, size); }
            if (*c == '.') { return DFA::num(token, c, size); }
            if (*c == '\'' || *c == '"') { return DFA::string(token, c, size); }
            return DFA::symbol(token, c, size);
        }

    }  // namespace DFA

    namespace Token {

        struct Generator::Impl {
            unique_istream in;
            std::string line;

            bool finished = false;
            std::unique_ptr<DFA::State> state;

            Token::Contents token;

            Impl(unique_istream&& in) :
                in{std::move(in)}, state{std::make_unique<DFA::State>()} {
                next();
            }

            void next() {
                if (finished) { return; }
                if (state->size == 0) {
                    if (getline(*in, line)) {
                        state = std::make_unique<DFA::State>(
                            DFA::State{line.c_str(), line.size()});
                        if (state->size == 0) { throw 1; }
                    } else {
                        finished = true;
                        token.set(Token::Kind::__EOF__, 0ULL);
                        return;
                    }
                }
                state = std::make_unique<DFA::State>(
                    DFA::start(token, state->c, state->size));
            }
        };

        Generator::Generator(const std::string& input) :
            impl{std::make_unique<Generator::Impl>(calcpp::sstream(input))} {}

        Generator::Generator(unique_istream&& in) :
            impl{std::make_unique<Generator::Impl>(std::move(in))} {}

        Generator::~Generator() = default;

        Generator& Generator::next() {
            impl->next();
            return *this;
        }
        Generator& Generator::operator++() { return next(); }

        bool Generator::finished() const { return impl->finished; }

        // Accessor methods for current token
        Token::Kind Generator::kind() const { return impl->token.kind; }
        std::string_view Generator::view() const {
            switch (impl->token.kind) {
                case Token::Kind::NUM:
                case Token::Kind::COMPLEX:
                case Token::Kind::HEX:
                case Token::Kind::BIN:
                    THROW_ERROR("Cannot get string view from numeric token");
                default:
                    return impl->token.val.str;
            }
        }
        std::string Generator::str() const { return std::string(view()); }
        double Generator::value() const {
            switch (impl->token.kind) {
                case Token::Kind::NUM:
                case Token::Kind::COMPLEX:
                    return impl->token.val.d;
                default:
                    THROW_ERROR("Cannot get value from non-numeric token");
            }
        }
        unsigned long long Generator::ull() const {
            switch (impl->token.kind) {
                case HEX:
                case BIN:
                    return impl->token.val.ull;
                default:
                    THROW_ERROR("Cannot get value from non-numeric token");
            }
        }

        Token::Iterator Generator::begin() { return Token::Iterator(this); }
        Token::Iterator Generator::end() { return Token::Iterator(this); }

        Iterator::Iterator(Token::Generator* generator) : generator{generator} {}

        const Token::Generator* Iterator::operator*() const { return generator; }
        bool Iterator::operator!=(const Token::Iterator& other) const {
            return generator != other.generator || !(generator->finished());
        }
        Iterator& Iterator::operator++() {
            generator->next();
            return *this;
        }

    }  // namespace Token

    Token::Generator scan(const std::string& input) { return Token::Generator(input); }
    Token::Generator scan(unique_istream&& in) {
        return Token::Generator(std::move(in));
    }

    std::ostream& operator<<(std::ostream& out, const Token::Generator& generator) {
        switch (generator.kind()) {
            case Token::Kind::NUM:
            case Token::Kind::COMPLEX:
                return out << generator.value();
            case Token::Kind::HEX:
            case Token::Kind::BIN:
                return out << generator.ull();
            default:
                return out << generator.view();
        }
    }

}  // namespace calcpp
