#pragma once

#include "parser.h"

class ShuntingYard: public Parser {

    

    public:
        ShuntingYard();

        expression parse(const std::list<Scanner::Token>& tokens) override;
};
