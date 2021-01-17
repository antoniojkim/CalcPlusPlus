#pragma once

#include <list>

#include "../Expressions/Expression.h"
#include "../Scanner/Scanner.h"

namespace calcpp {
    class Parser {
      public:
        virtual expression parse(TokenCollection& tokens) const = 0;
    };
}  // namespace calcpp
