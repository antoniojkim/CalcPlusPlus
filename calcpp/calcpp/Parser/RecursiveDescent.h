#pragma once

#include "parser.h"

namespace calcpp {
    class RecursiveDescent: public Parser {
      public:
        RecursiveDescent();
        ~RecursiveDescent();

        std::vector<AST> parse(TokenCollection& tokens) const override;
    };
}  // namespace calcpp
