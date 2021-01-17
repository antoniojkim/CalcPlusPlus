#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include "GreekLetters.h"

using namespace std;
using namespace calcpp;

int main() {
    std::string inf = "\u221E";
    cout << inf << endl;
    cout << inf.size() << endl;

    for (int i = 0; i < numGreekLetters; ++i) {
        const char* letter = getGreekLetter(i);
        cout << greekLetterNames[i] << "\t" << letter << "\t" << std::strlen(letter)
             << endl;

        int index = getGreekLetterIndex(greekLetters[i]);
        assert(index == i);

        if (i > 0) {
            int cmp = std::strcmp(greekLetters[i - 1], greekLetters[i]);
            if (cmp >= 0) {
                cout << cmp << "\t" << greekLetters[i - 1] << " >= " << greekLetters[i]
                     << endl;
            }
            assert(cmp < 0);
        }
    }
}
