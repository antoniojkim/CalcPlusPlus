#pragma once

#include <string>
#include <utility>
#include <vector>

#include "AST.h"

namespace calcpp {

    class CallAST: public AbstractSyntaxTree {
        const std::string callee;
        const std::vector<AST> args;

        CallAST(const std::string& callee, std::vector<AST>&& args) :
            callee{callee}, args{std::move(args)} {}

      public:
        REGISTER_AST(CallAST);

        std::ostream& repr(std::ostream& out) const override {
            out << "call(" << callee << ", (";
            for (auto& arg : args) { arg->repr(out) << ", "; }
            return out << "))";
        }
    };

    // Create an alias for CallAST construction
    AST_ALIAS(CallAST, call)

};  // namespace calcpp
