#pragma once

namespace calcpp {

    typedef unsigned int FType;  // define the fundamental type undelying the type enum

    enum class Type : FType {
        // begin sourcegen types
        NONE       = 0b0000000000000001,
        EMPTY      = 0b0000000000000010,
        INVALID    = 0b0000000000000100,
        NUM        = 0b0000000000001000,
        COMPLEX    = 0b0000000000010000,
        HEX        = 0b0000000000100000,
        BIN        = 0b0000000001000000,
        VAR        = 0b0000000010000000,
        VARARG     = 0b0000000100000000,
        CONSTANT   = 0b0000001000000000,
        TUPLE      = 0b0000010000000000,
        MATRIX     = 0b0000100000000000,
        STRING     = 0b0001000000000000,
        CALLABLE   = 0b0010000000000000,
        EVALUABLE  = 0b0100000000000000,
        ASSIGNMENT = 0b1000000000000000
        // end sourcegen
    };

    inline FType operator|(Type t1, Type t2) { return (FType) t1 | (FType) t2; }
    inline FType operator|(FType t1, Type t2) { return t1 | (FType) t2; }
    inline FType operator|(Type t1, FType t2) { return (FType) t1 | t2; }

    typedef long double Double;

}  // namespace calcpp
