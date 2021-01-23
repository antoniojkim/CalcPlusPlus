#pragma once

#include "../Expressions/Types.h"
#include "../Scanner/Scanner.h"

namespace calcpp {

    namespace operators {

        int precedence(const Token::Kind kind);
        bool rightAssociative(const Token::Kind kind);
        bool singleOperator(const Token::Kind kind);

        expression get(const Token::Kind kind);

    }  // namespace operators

    bool isOperator(const Token::Kind kind);

}  // namespace calcpp
