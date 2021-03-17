#pragma once

// #include "../Expressions/Expression.h"
// #include "../Expressions/Types.h"
#include "../AST/AST.h"
#include "../Scanner/Scanner.h"

namespace calcpp {

    namespace operators {

        int precedence(const Token::Kind kind);
        bool isRightAssociative(const Token::Kind kind);
        bool isSingle(const Token::Kind kind);

        // expression get(const Token::Kind kind);
        AST get(const Token::Kind kind, AST lhs, AST rhs);

        /*
          // begin sourcegen operators
          extern const expression add;
          extern const expression bitwise_and;
          extern const expression bitwise_or;
          extern const expression bitwise_xor;
          extern const expression div;
          extern const expression eq;
          extern const expression floordiv;
          extern const expression lshift;
          extern const expression mod;
          extern const expression mul;
          extern const expression pow;
          extern const expression rshift;
          extern const expression sub;
          // end sourcegen
        */

    }  // namespace operators

    bool isOperator(const Token::Kind kind);

    bool isSupportedOperator(const Token::Kind kind);
    // expression getOperator(const Token::Kind kind);

}  // namespace calcpp
