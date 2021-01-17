#pragma once

#ifndef __GREEK_LETTERS_H__
#define __GREEK_LETTERS_H__

#include <string>

#include "../Utils/BinarySearch.h"
#include "../Utils/Exception.h"

namespace calcpp {

    constexpr const int numGreekLetters =
        // begin sourcegen numGreekLetters
        49
        // end sourcegen
        ;
    constexpr const char* greekLetterNames[numGreekLetters] = {
        // begin sourcegen greekLetterNames
        "Alpha", "Beta",   "Chi",   "Delta", "Epsilon", "Eta",     "Gamma", "Iota",
        "Kappa", "Lambda", "Mu",    "Nu",    "Omega",   "Omicron", "Phi",   "Pi",
        "Psi",   "Rho",    "Sigma", "Tau",   "Theta",   "Upsilon", "Xi",    "Zeta",
        "alpha", "beta",   "chi",   "delta", "epsilon", "eta",     "gamma", "iota",
        "kappa", "lambda", "mu",    "nu",    "omega",   "omicron", "phi",   "pi",
        "psi",   "rho",    "sigma", "tau",   "theta",   "upsilon", "vphi",  "xi",
        "zeta"
        // end sourcegen
    };
    constexpr const int greekLetterIndices[numGreekLetters] = {
        // begin sourcegen greekLetterIndices
        0,  1,  21, 3,  4,  6,  2,  8,  9,  10, 11, 12, 23, 14, 20, 15, 22,
        16, 17, 18, 7,  19, 13, 5,  24, 25, 45, 27, 28, 30, 26, 32, 33, 34,
        35, 36, 47, 38, 44, 39, 46, 40, 41, 42, 31, 43, 48, 37, 29
        // end sourcegen
    };
    constexpr const int shortestGreekLetterName =
        // begin sourcegen shortestGreekLetterName
        2
        // end sourcegen
        ;
    constexpr const int longestGreekLetterName =
        // begin sourcegen longestGreekLetterName
        7
        // end sourcegen
        ;
    constexpr const char* greekLetters[numGreekLetters] = {
        // begin sourcegen greekLetters
        "\u0391", "\u0392", "\u0393", "\u0394", "\u0395", "\u0396", "\u0397", "\u0398",
        "\u0399", "\u039a", "\u039b", "\u039c", "\u039d", "\u039e", "\u039f", "\u03a0",
        "\u03a1", "\u03a3", "\u03a4", "\u03a5", "\u03a6", "\u03a7", "\u03a8", "\u03a9",
        "\u03b1", "\u03b2", "\u03b3", "\u03b4", "\u03b5", "\u03b6", "\u03b7", "\u03b8",
        "\u03b9", "\u03ba", "\u03bb", "\u03bc", "\u03bd", "\u03be", "\u03bf", "\u03c0",
        "\u03c1", "\u03c3", "\u03c4", "\u03c5", "\u03c6", "\u03c7", "\u03c8", "\u03c9",
        "\u03d5"
        // end sourcegen
    };

    /*
    Returns index of the constant in the constants array.

    Uses binary search under the hood to search for the index.

    Parameters
    ----------
    name: The name of the constantaddMissingRParens
    The index or -1 if the provided name is not a constant.
    */
    CONSTEXPR_BINARY_SEARCH(getGreekLetterNameIndex, greekLetterNames, numGreekLetters)

    CONSTEXPR_BINARY_SEARCH(getGreekLetterIndex, greekLetters, numGreekLetters)

    constexpr const char* getGreekLetter(const int index) {
        return greekLetters[greekLetterIndices[index]];
    }
    static const char* getGreekLetter(const std::string& name) {
        int index = getGreekLetterNameIndex(name);
        if (index == -1) { THROW_VALUE_ERROR("Invalid Greek Letter: " << name); }
        return getGreekLetter(index);
    }

}  // namespace calcpp

#endif  // __GREEK_LETTERS_H__
