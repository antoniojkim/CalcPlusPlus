#pragma once

#include <list>
#include <map>
#include <memory>
#include <string>
#include <gsl/gsl_math.h>

#include "Expressions/Expression.h"
#include "Scanner/scanner.h"
#include "Parser/parser.h"
#include "Utils/exceptions.h"

class MathEngine {

    std::unique_ptr<Parser> parser;
    Variables variables;

    public:
        MathEngine();

        std::list<Scanner::Token> scan(const std::string& input);

        expression parse(const std::string& input);
        expression operator()(const std::string& input);

        expression evaluate(const std::string& input);
};

