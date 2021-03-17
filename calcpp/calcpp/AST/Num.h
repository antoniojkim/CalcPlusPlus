#pragma once

#include "AST.h"

namespace calcpp {

    class NumAST: public AbstractSyntaxTree {
        double val;

        NumAST(double val) : val{val} {}

      public:
        REGISTER_AST(NumAST);

        std::ostream& repr(std::ostream& out) const override {
            return out << "num(" << val << ")";
        }
    };

    // Create an alias for NumAST construction
    AST_ALIAS(NumAST, num)

};  // namespace calcpp
