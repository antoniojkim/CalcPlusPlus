
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "../../Utils/Exception.h"
#include "RandomDistributionDirectory.h"
#include "RandomDistributions.h"
#include "Distributions/Gauss.h"

using namespace std;

/***************************************************
 ********** Random Distribution Functions **********
 ***************************************************/

const RandomDistribution randomDistributions[numDistributions] = {
    {randomDistributions}
};

RandomDistribution get_random_distribution(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution(index);
}
RandomDistribution get_random_distribution(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributions[distributionIndex];
}


/***************************************************
 ************* Random Distribution PDFs ************
 ***************************************************/

const RandomDistributionFunction randomDistributionPDFs[numDistributions] = {
    {randomDistributionPDFs}
};

RandomDistributionFunction get_random_distribution_pdf(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_pdf(index);
}
RandomDistributionFunction get_random_distribution_pdf(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionPDFs[distributionIndex];
}


/***************************************************
 ************ Random Distribution CDF_Ps ***********
 ***************************************************/

const RandomDistributionFunction randomDistributionCDFPs[numDistributions] = {
    {randomDistributionCDFPs}
};

RandomDistributionFunction get_random_distribution_cdf_P(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_cdf_P(index);
}
RandomDistributionFunction get_random_distribution_cdf_P(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionCDFPs[distributionIndex];
}


/***************************************************
 ************ Random Distribution CDF_Qs ***********
 ***************************************************/

const RandomDistributionFunction randomDistributionCDFQs[numDistributions] = {
    {randomDistributionCDFQs}
};

RandomDistributionFunction get_random_distribution_cdf_Q(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_cdf_Q(index);
}
RandomDistributionFunction get_random_distribution_cdf_Q(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionCDFQs[distributionIndex];
}


/***************************************************
 ********** Random Distribution CDF_Pinvs **********
 ***************************************************/

const RandomDistributionFunction randomDistributionCDFPinvs[numDistributions] = {
    {randomDistributionCDFPinvs}
};

RandomDistributionFunction get_random_distribution_cdf_Pinv(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_cdf_Pinv(index);
}
RandomDistributionFunction get_random_distribution_cdf_Pinv(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionCDFPinvs[distributionIndex];
}


/***************************************************
 *********** Random Distribution CDF_Qinvs *********
 ***************************************************/

const RandomDistributionFunction randomDistributionCDFQinvs[numDistributions] = {
    {randomDistributionCDFQinvs}
};

RandomDistributionFunction get_random_distribution_cdf_Qinv(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_cdf_Qinv(index);
}
RandomDistributionFunction get_random_distribution_cdf_Qinv(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionCDFQinvs[distributionIndex];
}


/***************************************************
 ********** Random Distribution Expectation ********
 ***************************************************/

const RandomDistribution randomDistributionExp[numDistributions] = {
    {randomDistributionExp}
};

RandomDistribution get_random_distribution_Exp(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_Exp(index);
}
RandomDistribution get_random_distribution_Exp(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionExp[distributionIndex];
}


/***************************************************
 *********** Random Distribution Variance **********
 ***************************************************/

const RandomDistribution randomDistributionVar[numDistributions] = {
    {randomDistributionVar}
};

RandomDistribution get_random_distribution_Var(const string& name){
    int index = getDistributionIndex(name);
    if (index == -1){
        throw Exception("Unknown Random Distribution: ", name);
    }
    return get_random_distribution_Var(index);
}
RandomDistribution get_random_distribution_Var(int distributionIndex){
    if (distributionIndex < 0 || distributionIndex >= numDistributions){
        throw Exception("Invalid Random Distribution Index: ", distributionIndex);
    }
    return randomDistributionVar[distributionIndex];
}
