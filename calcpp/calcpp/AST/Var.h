#pragma once

#include <string>

#include "AST.h"

namespace calcpp {

    class VarAST: public AbstractSyntaxTree {
        const std::string name;

        VarAST(const std::string& name) : name{name} {}

      public:
        REGISTER_AST(VarAST);

        std::ostream& repr(std::ostream& out) const override {
            return out << "var(" << name << ")";
        }
    };

    // Create an alias for VarAST construction
    AST_ALIAS(VarAST, var)

};  // namespace calcpp
