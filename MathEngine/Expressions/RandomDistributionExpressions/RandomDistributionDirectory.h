#pragma once

#include <list>
#include <string>

#include "../Expression.h"

typedef double (*RandomDistribution)(const std::list<expression>& args, const Variables& vars);
RandomDistribution get_random_distribution(const std::string& name);
RandomDistribution get_random_distribution(int distributionIndex);

typedef double (*RandomDistributionFunction)(double x, const std::list<expression>& args, const Variables& vars);
RandomDistributionFunction get_random_distribution_pdf(const std::string& name);
RandomDistributionFunction get_random_distribution_pdf(int distributionIndex);

RandomDistributionFunction get_random_distribution_cdf_P(const std::string& name);
RandomDistributionFunction get_random_distribution_cdf_P(int distributionIndex);

RandomDistributionFunction get_random_distribution_cdf_Q(const std::string& name);
RandomDistributionFunction get_random_distribution_cdf_Q(int distributionIndex);

RandomDistributionFunction get_random_distribution_cdf_Pinv(const std::string& name);
RandomDistributionFunction get_random_distribution_cdf_Pinv(int distributionIndex);

RandomDistributionFunction get_random_distribution_cdf_Qinv(const std::string& name);
RandomDistributionFunction get_random_distribution_cdf_Qinv(int distributionIndex);

RandomDistribution get_random_distribution_Exp(const std::string& name);
RandomDistribution get_random_distribution_Exp(int distributionIndex);

RandomDistribution get_random_distribution_Var(const std::string& name);
RandomDistribution get_random_distribution_Var(int distributionIndex);
