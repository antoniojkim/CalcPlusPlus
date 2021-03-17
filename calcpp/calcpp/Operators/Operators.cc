
#include "Operators.h"
#include "../AST/BinaryOperator.h"
#include "../Utils/Exception.h"
// #include "Functions.h"

namespace calcpp {

    namespace operators {

        constexpr const int size =
            // begin sourcegen size
            49
            // end sourcegen
            ;
        constexpr const int offset =
            // begin sourcegen offset
            21
            // end sourcegen
            ;
        constexpr const int precedences[size] = {
            // begin sourcegen precedences
            -8,  -5,  -11, -15, -16, 2,   -7,  -17, -17, 2,   -1, -3,  -3,
            -3,  -3,  2,   -9,  -15, -9,  -15, -10, -10, -12, 2,  -10, -10,
            -12, 2,   2,   -14, 2,   -15, 2,   -6,  -4,  -13, 2,  -17, 2,
            -17, -17, -15, 2,   -15, -15, 2,   -16, -10, 2
            // end sourcegen
        };
        constexpr const bool single[size] = {
            // begin sourcegen single
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            // end sourcegen
        };

        inline int _abs(int x) { return x >= 0 ? x : -x; }

        int precedence(const Token::Kind kind) {
            return _abs(precedences[int(kind) - offset]);
        }
        bool isRightAssociative(const Token::Kind kind) {
            return precedences[int(kind) - offset] > 0;
        }

        bool isSingle(const Token::Kind kind) { return single[int(kind) - offset]; }

        AST get(const Token::Kind kind, AST lhs, AST rhs) {
            switch (kind) {
                case Token::Kind::PLUS:
                    return calcpp::add(lhs, rhs);
                case Token::Kind::MINUS:
                    return calcpp::subtract(lhs, rhs);
                case Token::Kind::STAR:
                    return calcpp::multiply(lhs, rhs);
                case Token::Kind::SLASH:
                    return calcpp::divide(lhs, rhs);
                default:
                    THROW_ERROR("Unsupported operator: " << kind);
            }
        }

    }  // namespace operators

    bool isOperator(const Token::Kind kind) {
        return (int(kind) - operators::offset) >= 0;
    }

    bool isSupportedOperator(const Token::Kind kind) {
        switch (kind) {
            case Token::Kind::PLUS:
            case Token::Kind::MINUS:
            case Token::Kind::STAR:
            case Token::Kind::SLASH:
                return true;
            default:
                return false;
        }
    }
    // expression getOperator(const Token::Kind kind) {
    // switch (kind) {
    // // begin sourcegen operator_cases
    // case Token::Kind::PLUS:
    // return calcpp::operators::add;
    // case Token::Kind::EQUALS:
    // return calcpp::operators::eq;
    // case Token::Kind::COLON_EQUALS:
    // return calcpp::operators::eq;
    // case Token::Kind::L_ARROW:
    // return calcpp::operators::eq;
    // case Token::Kind::LT_LT:
    // return calcpp::operators::lshift;
    // case Token::Kind::GT_GT:
    // return calcpp::operators::rshift;
    // case Token::Kind::AMP:
    // return calcpp::operators::bitwise_and;
    // case Token::Kind::PIPE:
    // return calcpp::operators::bitwise_or;
    // case Token::Kind::CARET_PIPE:
    // return calcpp::operators::bitwise_xor;
    // case Token::Kind::SLASH:
    // return calcpp::operators::div;
    // case Token::Kind::PCT:
    // return calcpp::operators::mod;
    // case Token::Kind::SLASH_SLASH:
    // return calcpp::operators::floordiv;
    // case Token::Kind::CARET:
    // return calcpp::operators::pow;
    // case Token::Kind::STAR_STAR:
    // return calcpp::operators::pow;
    // case Token::Kind::STAR:
    // return calcpp::operators::mul;
    // case Token::Kind::MINUS:
    // return calcpp::operators::sub;
    // // end sourcegen
    // default:
    // THROW_ERROR("Invalid kind for operator: " << kind);
    // }
    // }

}  // namespace calcpp
