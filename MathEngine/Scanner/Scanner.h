#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace calcpp {
    struct Token {
        enum class Kind {
            NONE,
            EMPTY,
            NUM,
            COMPLEX,
            HEX,
            BIN,
            ID,

            // Symbols
            LPAREN,
            RPAREN,
            LBRACE,
            RBRACE,
            LCURLY,
            RCURLY,
            PLUS,
            PLUS_EQUALS,
            MINUS,
            MINUS_EQUALS,
            STAR,
            STAR_EQUALS,
            STAR_STAR,
            SLASH,
            SLASH_EQUALS,
            SLASH_SLASH,
            PCT,
            PCT_EQUALS,
            CARET,
            CARET_EQUALS,
            CARET_PIPE,
            PIPE,
            PIPE_PIPE,
            AMP,
            AMP_AMP,
            GT,
            GT_EQUALS,
            GT_GT,
            GT_GT_EQUALS,
            LT,
            LT_EQUALS,
            LT_LT,
            LT_LT_EQUALS,
            L_ARROW,
            R_ARROW,
            EQUALS,
            EQUALS_EQUALS,
            COLON,
            COLON_EQUALS,
            COLON_COLON,
            SEMICOLON,
            SEMICOLON_SEMICOLON,
            APOSTROPHE,
            QUOTE,
            STRING,
            BACKTICK,
            TILDE,
            TILDE_EQUALS,
            EXCL,
            EXCL_EXCL,
            EXCL_EQUALS,
            DOT,
            DOT_DOT,
            ELLIPSES,
            COMMA,
            QUESTION,
            DOLLAR,
            HASH,
            AT,
            BACKSLASH
        };

        const char* c_str;
        const size_t size;
        const Kind kind;

        std::string_view view() const;
    };

    typedef std::vector<Token> TokenCollection;

    TokenCollection scan(const std::string& equation);

}  // namespace calcpp
