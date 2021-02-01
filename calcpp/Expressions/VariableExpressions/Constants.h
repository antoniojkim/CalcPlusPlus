#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <cstring>
#include <string>

#include <gsl/gsl_math.h>

#include "../../Utils/BinarySearch.h"

namespace calcpp {
    constexpr const int numConstants =
        // begin sourcegen numConstants
        4
        // end sourcegen
        ;
    constexpr const char* constants[numConstants] = {
        // begin sourcegen constants
        "pi",
        "e",
        "gamma",
        "vphi"
        // end sourcegen
    };
    constexpr const double constantValues[numConstants] = {
        // begin sourcegen constantValues
        M_PI,
        M_E,
        M_EULER,
        1.6180339887498948482
        // end sourcegen
    };
    const std::string shortConstants[numConstants] = {
        // begin sourcegen shortConstants
        "π",
        "e",
        "γ",
        "ϕ"
        // end sourcegen
    };
    constexpr const char* constantLongValues[numConstants] = {
        // begin sourcegen constantLongValues
        "3."
        "141592653589793238462643383279502884197169399375105820974944592307816406286208"
        "99862803482534211706798214808651328",
        "2."
        "718281828459045235360287471352662497757247093699959574966967627724076630353547"
        "594571382178525166427427466391932",
        "0."
        "577215664901532860606512090082402431042159335939923598805767234884867726777664"
        "6709369470632917467495146314472498",
        "1."
        "618033988749894848204586834365638117720309179805762862135448622705260462818902"
        "44970720720418939113748475408807538"
        // end sourcegen
    };
    constexpr const int longestConstantName =
        // begin sourcegen longestConstantName
        5
        // end sourcegen
        ;
    constexpr const int shortestConstantName =
        // begin sourcegen shortestConstantName
        1
        // end sourcegen
        ;

    /*
    Returns index of the constant in the constants array.

    Uses binary search under the hood to search for the index.

    Parameters
    ----------
    name: The name of the constant

    Returns
    -------
    The index or -1 if the provided name is not a constant.
    */
    CONSTEXPR_BINARY_SEARCH(getConstantIndex, constants, numConstants)

    /*
    Returns the value of the constant at the provided index.

    Parameters
    ----------
    index: the index of the constant name

    Returns
    -------
    If the index is valid, it will return the number of arguments.
    If the index is not valid, the function will return 0.
    Note: a return value of -1 means that it accepts a variable number of parameters.
    */
    static double getConstantValue(const std::string& name) {
        int index = getConstantIndex(name.c_str());
        if (index != -1) { return constantValues[index]; }
        return GSL_NAN;
    }
    constexpr double getConstantValue(int index) {
        if (index >= 0 && index < numConstants) { return constantValues[index]; }
        return GSL_NAN;
    }

}  // namespace calcpp

#endif  // __CONSTANTS_H__
