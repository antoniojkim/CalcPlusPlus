#pragma once

#include <string>
#include <vector>

#include "AST.h"

namespace calcpp {

    class PrototypeAST: public AbstractSyntaxTree {
        const std::string name;
        const std::vector<std::string> args;

        PrototypeAST(const std::string& name, std::vector<std::string>&& args) :
            name{name}, args{std::move(args)} {}

      public:
        REGISTER_AST(PrototypeAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "prototype(" << name << ", (";
            bool first = true;
            for (auto& arg : args) {
                if (!first) {
                    out << ", ";
                } else {
                    first = false;
                }
                out << arg;
            }
            return out << "))";
        }
    };

    // Create an alias for PrototypeAST construction
    AST_ALIAS(PrototypeAST, prototype)

    class FunctionAST: public AbstractSyntaxTree {
        AST prototype;
        AST body;

        FunctionAST(AST prototype, AST body) : prototype{prototype}, body{body} {}

      public:
        REGISTER_AST(FunctionAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "function(";
            prototype->repr(out);
            out << ", ";
            body->repr(out);
            return out << ")";
        }
    };

    // Create an alias for FunctionAST construction
    AST_ALIAS(FunctionAST, function)

};  // namespace calcpp
