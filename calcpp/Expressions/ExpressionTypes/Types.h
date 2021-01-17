#pragma once

namespace calcpp {

    enum Type {
        // begin sourcegen types
        NONE      = 0b000000000000001,
        EMPTY     = 0b000000000000010,
        INVALID   = 0b000000000000100,
        NUM       = 0b000000000001000,
        COMPLEX   = 0b000000000010000,
        HEX       = 0b000000000100000,
        BIN       = 0b000000001000000,
        VAR       = 0b000000010000000,
        VARARG    = 0b000000100000000,
        CONSTANT  = 0b000001000000000,
        TUPLE     = 0b000010000000000,
        MATRIX    = 0b000100000000000,
        STRING    = 0b001000000000000,
        CALLABLE  = 0b010000000000000,
        EVALUABLE = 0b100000000000000
        // end sourcegen
    };

}  // namespace calcpp
