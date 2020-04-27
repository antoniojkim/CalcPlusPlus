
#include <iostream>

using namespace std;

#include <Catch2>
#include <MathEngine.h>

extern MathEngine engine;

void checkFormattedInput(const std::string& input, int cursorPosition, const std::string& expectedInput, int expectedCursorPosition){
    auto formattedInput = engine.formatInput(input, cursorPosition);
    if (formattedInput != expectedInput || cursorPosition != expectedCursorPosition){
        cout << "Formatted Input:           " << formattedInput << endl;
        cout << "Expected Input:            " << expectedInput << endl;
        cout << "Cursor Position:           " << cursorPosition << endl;
        cout << "Expected Cursor Position:  " << expectedCursorPosition << endl;
    }
    REQUIRE( ((formattedInput == expectedInput) && (cursorPosition == expectedCursorPosition)) );
}

TEST_CASE("Math Engine Tests", "[MathEngine]" ) {
    checkFormattedInput("123pi+456", 5, "123π+456", 4);
    checkFormattedInput("phi", 3, "φ", 1);
}
