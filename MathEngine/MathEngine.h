#ifndef __MATH_ENGINE_H__
#define __MATH_ENGINE_H__

#include <list>
#include <memory>
#include <string>
#include <gsl/gsl_math.h>

#include "Expressions/Expression.h"
#include "Scanner/scanner.h"
#include "Parser/parser.h"
#include "Utils/exceptions.h"

class MathEngine {

    Parser parser;

    public:
        std::list<Scanner::Token> scan(const std::string& input);

        std::unique_ptr<ParseTree> parse(const std::string& input);
        std::unique_ptr<ParseTree> parse(std::list<Scanner::Token>& tokens);

        expression eval(const std::string& input);
        expression eval(const std::string& input, const double& x, const double& y = GSL_NAN);
        expression operator()(const std::string& input);
        expression operator()(const std::string& input, const double& x, const double& y = GSL_NAN);
};

#endif // __MATH_ENGINE_H__
