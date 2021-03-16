#pragma once

#include <string>

#include "AST.h"

namespace calcpp {

    class BinaryOperatorAST: public AbstractSyntaxTree {
      protected:
        AST lhs, rhs;

        BinaryOperatorAST(AST lhs, AST rhs) : lhs{lhs}, rhs{rhs} {}
    };

    class AdditionAST: public BinaryOperatorAST {
        AdditionAST(AST lhs, AST rhs) : BinaryOperatorAST(lhs, rhs) {}

      public:
        REGISTER_AST(AdditionAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "add(";
            lhs->repr(out);
            out << ", ";
            rhs->repr(out);
            return out << ")";
        }
    };

    // Create an alias for AdditionAST construction
    AST_ALIAS(AdditionAST, add);

    class SubtractionAST: public BinaryOperatorAST {
        SubtractionAST(AST lhs, AST rhs) : BinaryOperatorAST(lhs, rhs) {}

      public:
        REGISTER_AST(SubtractionAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "subtract(";
            lhs->repr(out);
            out << ", ";
            rhs->repr(out);
            return out << ")";
        }
    };

    // Create an alias for SubtractionAST construction
    AST_ALIAS(SubtractionAST, subtract);

    class MultiplicationAST: public BinaryOperatorAST {
        MultiplicationAST(AST lhs, AST rhs) : BinaryOperatorAST(lhs, rhs) {}

      public:
        REGISTER_AST(MultiplicationAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "multiply(";
            lhs->repr(out);
            out << ", ";
            rhs->repr(out);
            return out << ")";
        }
    };

    // Create an alias for MultiplicationAST construction
    AST_ALIAS(MultiplicationAST, multiply);

    class DivisionAST: public BinaryOperatorAST {
        DivisionAST(AST lhs, AST rhs) : BinaryOperatorAST(lhs, rhs) {}

      public:
        REGISTER_AST(DivisionAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "divide(";
            lhs->repr(out);
            out << ", ";
            rhs->repr(out);
            return out << ")";
        }
    };

    // Create an alias for DivisionAST construction
    AST_ALIAS(DivisionAST, divide);

};  // namespace calcpp
