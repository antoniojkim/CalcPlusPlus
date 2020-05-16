#pragma once

#include <string>
#include <vector>

#include <gsl/gsl_complex.h>
#include <MathEngine.h>

extern MathEngine engine;

bool printDifference(const std::string& input, const expression expr, const double output, const double expected);
void requireIsEqual(const std::string& input, const double expected);

bool printDifference(const std::string& input, const expression expr, const std::string& output, const std::string& expected);
void requireIsEqual(const std::string& input, const std::string& expected, bool evaluate = false);

bool printDifference(const std::string& input, const expression expr, const expression output, const std::string& expected);
void requireExprIsEqual(const std::string& input, const std::string& expected);
