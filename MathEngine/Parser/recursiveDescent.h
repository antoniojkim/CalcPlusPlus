#pragma once

#include "parser.h"

class RecursiveDescent: public Parser {

    public:
        RecursiveDescent();

        expression parse(std::list<Scanner::Token>& tokens) override;
};
