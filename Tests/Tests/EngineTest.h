#pragma once

#include <string>
#include <vector>

#include <gsl/gsl_complex.h>
#include <MathEngine.h>

extern MathEngine engine;

bool printDifference(const std::string& input, const expression expression, const double& output, const double& expected);
void requireIsEqual(const std::string& input, const double& expected);

bool printDifference(const std::string& input, const expression expression, const std::string& output, const std::string& expected);
void requireIsEqual(const std::string& input, const std::string& expected, bool evaluate = false);

bool printDifference(const std::string& input, const expression expression, const gsl_complex& output, const gsl_complex& expected);
void requireIsEqual(const std::string& input, const gsl_complex& expected);

bool printDifference(const std::string& input, const expression expr, const expression output, const std::vector<double>& expected);
void requireIsEqual(const std::string& input, const std::vector<double>& expected);

bool printDifference(const std::string& input, const expression expr, const expression output, const std::vector<gsl_complex>& expected);
void requireIsEqual(const std::string& input, const std::vector<gsl_complex>& expected);

bool printDifference(const std::string& input, const expression expr, const expression output, const std::vector<std::vector<double>>& expected);
void requireIsEqual(const std::string& input, const std::vector<std::vector<double>>& expected);

bool printDifference(const std::string& input, const expression expr, const expression output, const std::vector<std::vector<double>>& expected);
void requireIsEqual(const std::string& input, const std::vector<std::vector<gsl_complex>>& expected);
