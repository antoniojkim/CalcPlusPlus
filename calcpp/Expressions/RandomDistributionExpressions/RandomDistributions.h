#pragma once

#ifndef __RANDOM_DISTRIBUTION_DIRECTORY_H__
#define __RANDOM_DISTRIBUTION_DIRECTORY_H__

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

constexpr const int numDistributions = 1;
constexpr const char* distributionNames[numDistributions] = {
    "Gauss"
};
constexpr const int distributionNumArgs[numDistributions] = {
    1
};

/*
Returns index of the random distribution in the distributionNames array.

Uses binary search under the hood to search for the index.

Parameters
----------
name: The name of the random distribution

Returns
-------
The index or -1 if the provided name is not a random distribution.
*/
constexpr int getDistributionIndex(const char* name){
    int low = 0;
    int high = numDistributions - 1;
    while (true){
        if (low > high){
            return -1;
        }

        int mid = (low + high) / 2;
        int cmp = std::strcmp(name, distributionNames[mid]);
        if (cmp == 0){
            return mid;
        }
        else if (cmp < 0){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return -1;
}
inline int getDistributionIndex(const std::string& name){
    return getDistributionIndex(name.c_str());
}

/*
Returns the number of arguments for the random distribution at the provided index.

Parameters
----------
index: the index of the random distribution name

Returns
-------
If the index is valid, it will return the number of arguments.
If the index is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
constexpr int getDistributionNumArgs(int index){
    if (index >= 0 && index < numDistributions){
        return distributionNumArgs[index];
    }
    return 0;
}

/*
Returns the number of arguments that a random distribution takes in.

Parameters
----------
name: The name of the random distribution

Returns
-------
If the name is a valid function it will return the number of arguments.
If the name is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
inline int getDistributionNumArgs(const std::string& name){
    return getDistributionNumArgs(getDistributionIndex(name));
}

#endif // __RANDOM_DISTRIBUTION_DIRECTORY_H__
