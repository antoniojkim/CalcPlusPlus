#pragma once

#include <vector>

#include "../AST/AST.h"
#include "../Scanner/Scanner.h"

namespace calcpp {
    class Parser {
      public:
        virtual ~Parser() {}

        virtual std::vector<AST> parse(TokenCollection& tokens) const = 0;
    };
}  // namespace calcpp
