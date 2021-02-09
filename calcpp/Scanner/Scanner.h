#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "../Expressions/Types.h"

namespace calcpp {

    namespace Token {
        enum Kind {
            // begin sourcegen kinds
            NONE,
            EMPTY,
            NUM,
            COMPLEX,
            HEX,
            BIN,
            ID,
            INF,
            GREEK,
            LPAREN,
            RPAREN,
            LBRACE,
            RBRACE,
            LCURLY,
            RCURLY,
            QUOTE,
            STRING,
            BACKTICK,
            HASH,
            BACKSLASH,
            AMP,
            AMP_AMP,
            APOSTROPHE,
            AT,
            CARET,
            CARET_EQUALS,
            CARET_PIPE,
            COLON,
            COLON_COLON,
            COLON_EQUALS,
            COMMA,
            DOLLAR,
            DOT,
            DOT_DOT,
            ELLIPSIS,
            EQUALS,
            EQUALS_EQUALS,
            EXCL,
            EXCL_EQUALS,
            EXCL_EXCL,
            GT,
            GT_EQUALS,
            GT_GT,
            GT_GT_EQUALS,
            LT,
            LT_EQUALS,
            LT_LT,
            LT_LT_EQUALS,
            L_ARROW,
            MINUS,
            MINUS_EQUALS,
            PCT,
            PCT_EQUALS,
            PIPE,
            PIPE_PIPE,
            PLUS,
            PLUS_EQUALS,
            QUESTION,
            R_ARROW,
            SEMICOLON,
            SEMICOLON_SEMICOLON,
            SLASH,
            SLASH_EQUALS,
            SLASH_SLASH,
            STAR,
            STAR_EQUALS,
            STAR_STAR,
            TILDE,
            TILDE_EQUALS
            // end sourcegen
        };

        struct Class {
            union {
                struct {
                    const char* c_str;
                    const size_t size;
                } str;
                Double value;
                unsigned long long ull;
            } data;

            const Kind kind;

            Class(const char* c_str, size_t size, Kind kind);
            Class(Double value, Kind kind);
            Class(unsigned long long ull, Kind kind);

            std::string_view view() const;
            std::string str() const { return std::string(view()); }
            const char* c_str() const;
            Double value() const;
            unsigned long long ull() const;

            friend bool operator==(const Class& token, const Kind kind);
            friend std::ostream& operator<<(std::ostream&, const Kind);
        };

    }  // namespace Token

    typedef Token::Class TokenClass;

    typedef std::vector<TokenClass> TokenCollection;

    TokenCollection scan(const std::string& equation);

    bool isPreImplicit(const Token::Kind kind);
    bool isPostImplicit(const Token::Kind kind);

}  // namespace calcpp
