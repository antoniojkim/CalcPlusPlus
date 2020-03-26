#pragma once

#include <list>

#include "../Scanner/scanner.h"
#include "../Expressions/Expression.h"

class Parser {

    public:
        virtual expression parse(const std::list<Scanner::Token>& tokens) = 0;

};
