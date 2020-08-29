#include <cstring>
#include <string>

#include "../capi.h"


extern "C" {

    MathEngine* new_MathEngine(){ return new MathEngine(); }
    void delete_MathEngine(MathEngine* engine){ delete engine; }


    char* formatInput(MathEngine* engine, char* input, int* cursorPosition){
        auto s = engine->formatInput(std::string(input), *cursorPosition);
        char* newInput = (char*) malloc((s.size() + 1)*sizeof(char));
        strcpy(newInput, s.c_str());
        return newInput;
    }
    char* evaluateOutput(MathEngine* engine, char* input, char* output){
        auto s = engine->evaluateOutput(std::string(input), std::string(output));
        char* newoutput = (char*) malloc((s.size() + 1)*sizeof(char));
        strcpy(newoutput, s.c_str());
        return newoutput;
    }

}
