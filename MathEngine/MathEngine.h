#ifndef __MATH_ENGINE_H__
#define __MATH_ENGINE_H__

#include <list>
#include <string>

// #include "Parser/StringUtils.h"
#include "Scanner/scanner.h"
#include "Utils/exceptions.h"

class MathEngine {

    public:
        std::list<Scanner::Token> scan(const std::string&);

};

#endif // __MATH_ENGINE_H__
