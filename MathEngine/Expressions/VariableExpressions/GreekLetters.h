#pragma once

#ifndef __GREEK_LETTERS_H__
#define __GREEK_LETTERS_H__

#include <cstring>
#include <string>

#include <gsl/gsl_math.h>

constexpr const int numGreekLetters = 49;
constexpr const char* greekLetterNames[numGreekLetters] = {
	"Alpha", "Beta", "Chi", "Delta", "Epsilon", "Eta", "Gamma", "Iota", "Kappa", "Lambda",
	"Mu", "Nu", "Omega", "Omicron", "Phi", "Pi", "Psi", "Rho", "Sigma", "Tau", "Theta",
	"Upsilon", "Xi", "Zeta", "alpha", "beta", "chi", "delta", "epsilon", "eta", "gamma",
	"iota", "kappa", "lambda", "mu", "nu", "omega", "omicron", "phi", "pi", "psi", "rho",
	"sigma", "tau", "theta", "upsilon", "vphi", "xi", "zeta"
};
constexpr const int shortestGreekLetterName = 2;
constexpr const int longestGreekLetterName = 7;
constexpr const int greekLetterLength = 2;
const std::string greekLetters[numGreekLetters] = {
	u8"\u0391", u8"\u0392", u8"\u03A7", u8"\u0394", u8"\u0395", u8"\u0397", u8"\u0393",
	u8"\u0399", u8"\u039A", u8"\u039B", u8"\u039C", u8"\u039D", u8"\u03A9", u8"\u039F",
	u8"\u03A6", u8"\u03A0", u8"\u03A8", u8"\u03A1", u8"\u03A3", u8"\u03A4", u8"\u0398",
	u8"\u03A5", u8"\u039E", u8"\u0396", u8"\u03B1", u8"\u03B2", u8"\u03C7", u8"\u03B4",
	u8"\u03B5", u8"\u03B7", u8"\u03B3", u8"\u03B9", u8"\u03BA", u8"\u03BB", u8"\u03BC",
	u8"\u03BD", u8"\u03C9", u8"\u03BF", u8"\u03C6", u8"\u03C0", u8"\u03C8", u8"\u03C1",
	u8"\u03C3", u8"\u03C4", u8"\u03B8", u8"\u03C5", u8"\u03d5", u8"\u03BE", u8"\u03B6"
};

/*
Returns index of the constant in the constants array.

Uses binary search under the hood to search for the index.

Parameters
----------
name: The name of the constantaddMissingRParens
The index or -1 if the provided name is not a constant.
*/
static constexpr int getGreekLetterNameIndex(const char* name){
    int low = 0;
    int high = numGreekLetters - 1;
    while (true){
        if (low > high){
            return -1;
        }

        int mid = (low + high) / 2;
        int cmp = std::strcmp(name, greekLetterNames[mid]);
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
inline int getGreekLetterNameIndex(const std::string& name){
    return getGreekLetterNameIndex(name.c_str());
}

static int getGreekLetterIndex(const std::string& name){
    if (name.size() <= greekLetterLength){
        for (int i = 0; i < numGreekLetters; ++i){
            if (name == greekLetters[i]){
                return i;
            }
        }
    }
    return -1;
}

#endif // __GREEK_LETTERS_H__
