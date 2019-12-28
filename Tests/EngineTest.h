#ifndef __TEST_H__
#define __TEST_H__

#include <string>

#include "../MathEngine/MathEngine.h"

extern MathEngine engine;

bool printDifference(expression& expression, const double& output, const double& expected);
void requireIsEqual(const std::string& input, const double& expected);

bool printDifference(expression& expression, const std::string& output, const std::string& expected);
void requireIsEqual(const std::string& input, const std::string& expected);

#endif // __TEST_H__
