#pragma once

#include <list>
#include <memory>
#include <string>
#include <gsl/gsl_math.h>

#include "Expressions/Expression.h"
#include "Scanner/scanner.h"
#include "Parser/parser.h"
#include "Utils/exceptions.h"

class MathEngine {

    std::unique_ptr<Parser> parser;

    public:
        MathEngine();

        std::list<Scanner::Token> scan(const std::string& input);

        expression eval(const std::string& input);
        expression eval(const std::string& input, const double& x, const double& y = GSL_NAN);
        expression operator()(const std::string& input);
        expression operator()(const std::string& input, const double& x, const double& y = GSL_NAN);
};

