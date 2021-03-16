#include <cassert>
#include <charconv>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <tuple>
#include <vector>

// #include "../Expressions/ExpressionTypes/Types.h"
#include "../Functions/Operators.h"
#include "../Scanner/Scanner.h"
#include "../Utils/Exception.h"
// #include "../Utils/MultiStack.h"

#include "../AST/AST.h"
#include "../AST/BinaryOperator.h"
#include "../AST/Call.h"
#include "../AST/Function.h"
#include "../AST/Num.h"
#include "../AST/Var.h"

using namespace std;
using namespace calcpp;

namespace Parser {

    typedef TokenCollection::iterator TokenIterator;

    // Get next token
    inline void next(TokenIterator& token) { ++token; }

    AST ParseExpression(TokenIterator& token);

    // numberexpr := number
    AST ParseNum(TokenIterator& token) {
        auto result = calcpp::num(token->value());
        next(token);
        return result;
    }

    // parenexpr := '(' expression ')'
    AST ParseParenExpr(TokenIterator& token) {
        next(token);  // eat (
        auto result = ParseExpression(token);
        if (!result) return nullptr;

        switch (token->kind) {
            case Token::Kind::RPAREN:
                break;
            default:
                THROW_ERROR("Expected Closing Parenthesis. Got: " << token->kind);
        }
        next(token);
        return result;
    }

    // identifierexpr := identifier
    // identifierexpr := identifier '(' expression* ')'
    AST ParseIdentifierExpr(TokenIterator& token) {
        std::string name = token->str();
        next(token);  // eat identifier

        switch (token->kind) {
            case Token::Kind::LPAREN: {
                next(token);  // eat (
                std::vector<AST> args;
                if (token->kind != Token::Kind::RPAREN) {
                    while (true) {
                        auto arg = ParseExpression(token);
                        if (arg) {
                            args.emplace_back(arg);
                        } else {
                            return nullptr;
                        }

                        if (token->kind == Token::Kind::RPAREN) { break; }
                        if (token->kind != Token::Kind::COMMA) {
                            THROW_ERROR("Expected comma. Got: " << token->kind);
                        }
                        next(token);
                    }
                }
                next(token);  // eat )
                return calcpp::call(name, std::move(args));
            }
            default:
                auto result = calcpp::var(name);
                next(token);
                return result;
        }
    }

    //  primary := identifierexpr
    //  primary := numberexpr
    //  primary := parenexpr
    AST ParsePrimary(TokenIterator& token) {
        switch (token->kind) {
            case Token::Kind::NUM:
                return ParseNum(token);
            case Token::Kind::ID:
                return ParseIdentifierExpr(token);
            case Token::Kind::LPAREN:
                return ParseParenExpr(token);
            default:
                THROW_ERROR("Could not parse primary: " << token->kind);
        }
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

    //  binoprhs := ('op' primary)*
    AST ParseBinOpRHS(int exprPrecedence, AST lhs, TokenIterator& token) {
        while (true) {
            if (!calcpp::isOperator(token->kind) || !isSupportedOperator(token->kind)) {
                return lhs;
            }

            auto binOp = *token;
            int precedence = calcpp::operators::precedence(binOp.kind);

            next(token);  // eat binop

            auto rhs = ParsePrimary(token);
            if (!rhs) return nullptr;

            // If BinOp binds less tightly with RHS than the operator after RHS, let
            // the pending operator take RHS as its LHS.
            int nextPrecedence = calcpp::operators::precedence(token->kind);
            if (precedence < nextPrecedence) {
                rhs = ParseBinOpRHS(precedence + 1, rhs, token);
                if (!rhs) return nullptr;
            }

            // Merge lhs and rhs
            lhs = calcpp::operators::get(binOp.kind, lhs, rhs);
        }
    }

    //  expression := primary binoprhs
    AST ParseExpression(TokenIterator& token) {
        auto lhs = ParsePrimary(token);
        if (!lhs) return nullptr;

        return ParseBinOpRHS(0, lhs, token);
    }

    AST ParsePrototype(TokenIterator& token) {
        if (token->kind != Token::Kind::ID) {
            THROW_ERROR("Prototype expected ID token. Got: " << token->kind);
        }

        std::string name = token->str();
        next(token);

        if (token->kind != Token::Kind::LPAREN) {
            THROW_ERROR("Prototype expected ( token. Got: " << token->kind);
        }
        next(token);  // eat (

        std::vector<std::string> argnames;
        while (true) {
            if (token->kind == Token::Kind::ID) {
                argnames.emplace_back(token->str());
                next(token);
            } else if (token->kind == Token::Kind::COMMA) {
                next(token);  // eat ,
            } else if (token->kind == Token::Kind::RPAREN) {
                break;
            } else {
                THROW_ERROR("Prototype expected ID token. Got: " << token->kind);
            }
        }

        // success
        next(token);

        return calcpp::prototype(name, std::move(argnames));
    }

    // definition := 'def' prototype expression
    AST ParseDefinition(TokenIterator& token) {
        next(token);  // eat 'def'
        auto proto = ParsePrototype(token);
        if (!proto) return nullptr;

        auto expr = ParseExpression(token);
        if (!expr) return nullptr;

        return calcpp::function(proto, expr);
    }

    AST ParseTopLevelExpr(TokenIterator& token) {
        auto expr = ParseExpression(token);
        if (!expr) return nullptr;

        // Make an anonymous proto
        auto proto = calcpp::prototype("", std::vector<std::string>{});
        return calcpp::function(proto, expr);
    }

    std::vector<AST> parse(TokenCollection& tokens) {
        TokenIterator token = tokens.begin();
        TokenIterator end = tokens.end();

        std::vector<AST> statements;
        while (token != end) {
            switch (token->kind) {
                case Token::Kind::SEMICOLON:
                    next(token);
                    break;
                case Token::Kind::ID: {
                    if (token->view() == "def") {
                        statements.emplace_back(ParseDefinition(token));
                        break;
                    }
                }
                default:
                    statements.emplace_back(ParseExpression(token));
                    // THROW_ERROR("Unrecognized token: " << token->kind);
            }
        }
        return statements;
    }

}  // namespace Parser

int main() {
    const std::string input = "3*(2+4); 4 + 5 * 6; sin(3)";
    auto tokens = calcpp::scan(input);
    try {
        auto statements = Parser::parse(tokens);
        cout << "Parsed " << statements.size() << " statements" << endl;
        for (auto ast : statements) {
            cout << "    ";
            ast->repr(cout) << endl;
        }
    } catch (std::exception& e) { cout << e.what() << endl; }
}
