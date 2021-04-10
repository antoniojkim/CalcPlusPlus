#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "../Utils/Stream.h"

namespace calcpp {

    namespace Token {
        enum Kind {
            // begin sourcegen kinds
            __EOF__,
            NONE,
            EMPTY,
            NUM,
            COMPLEX,
            HEX,
            BIN,
            ID,
            CALL,
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

        class Iterator;

        class Generator {
            struct Impl;
            std::unique_ptr<Impl> impl;

          public:
            Generator(const std::string& input);
            Generator(unique_istream&& input);
            ~Generator();

            // Get the next token
            Generator& next();
            Generator& operator++();

            // True iff no more tokens to emit
            bool finished() const;

            // Accessor methods for current token
            Token::Kind kind() const;
            std::string_view view() const;
            std::string str() const;
            double value() const;
            unsigned long long ull() const;

            Token::Iterator begin();
            Token::Iterator end();
        };

        class Iterator {
            Token::Generator* generator;

          public:
            Iterator(Token::Generator*);

            const Token::Generator* operator*() const;
            bool operator!=(const Token::Iterator& other) const;
            Iterator& operator++();
        };

    }  // namespace Token

    Token::Generator scan(const std::string& equation);
    Token::Generator scan(unique_istream&& in);

    std::ostream& operator<<(std::ostream&, const Token::Kind);
    std::ostream& operator<<(std::ostream&, const Token::Generator&);

    bool isPreImplicit(const Token::Kind kind);
    bool isPostImplicit(const Token::Kind kind);

}  // namespace calcpp
