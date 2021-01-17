#pragma once

#include "parser.h"

namespace calcpp {
    class ModifiedShuntingYard: public Parser {
      public:
        ModifiedShuntingYard();

        expression parse(TokenCollection& tokens) const override;
    };
}  // namespace calcpp
