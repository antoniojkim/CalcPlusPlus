#pragma once

#include <string>

#include <MathEngine.h>

extern MathEngine engine;

bool printDifference(const std::string& input, expression& expression, const double& output, const double& expected);
void requireIsEqual(const std::string& input, const double& expected);

bool printDifference(const std::string& input, expression& expression, const std::string& output, const std::string& expected);
void requireIsEqual(const std::string& input, const std::string& expected);

