
#include "Operators.h"
#include "Functions.h"

namespace calcpp {

    namespace operators {

        constexpr const int size =
            // begin sourcegen size
            17
            // end sourcegen
            ;
        constexpr const int offset =
            // begin sourcegen offset
            20
            // end sourcegen
            ;
        constexpr const int precedences[size] = {
            // begin sourcegen precedences
            -8, -5, -11, -15, -16, -2, -7, -17, -17, -2, -1, -3, -3, -3, -3, -2,
            -9, -15, -9, -15, -10, -10, -12, -2, -10, -10, -12, -2, -2, -14, -2,
            -15, -2, -6, -4, -13, -2, -17, -2, -17, -17, -15, -2, -15, -15, -2,
            -16, -10, -2
            // end sourcegen
        };
        constexpr const bool single[size] = {
            // begin sourcegen single
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0
            // end sourcegen
        };

        inline int _abs(int x) { return x >= 0 ? x : -x; }

        int precedence(const Token::Kind kind) {
            return _abs(precedences[int(kind) - offset]);
        }
        bool rightAssociative(const Token::Kind kind) {
            return precedences[int(kind) - offset] > 0;
        }

        bool singleOperator(const Token::Kind kind) {
            return single[int(kind) - offset];
        }

    }  // namespace operators

    constexpr bool isOperator(const Token::Kind kind) {
        return (int(kind) - operators::offset) >= 0;
    }

    expression getOperator(const Token::Kind kind) { return None; }

}  // namespace calcpp
