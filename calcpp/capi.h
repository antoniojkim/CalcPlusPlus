#pragma once

#include "MathEngine.h"

extern "C" {

    MathEngine* new_MathEngine();
    void delete_MathEngine(MathEngine*);

    char* formatInput(MathEngine* engine, char* input, int* cursorPosition);
    char* evaluateOutput(MathEngine* engine, char* input, char* output);

}
