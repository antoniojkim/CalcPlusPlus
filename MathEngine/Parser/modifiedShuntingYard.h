#pragma once

#include "parser.h"

class ModifiedShuntingYard: public Parser {



    public:
        ModifiedShuntingYard();

        expression parse(std::list<Scanner::Token>& tokens) override;
};
