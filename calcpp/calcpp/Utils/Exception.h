#pragma once

#include <exception>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

namespace calcpp {
    using Exception = std::runtime_error;
}  // namespace calcpp

#define THROW_ERROR(msg)                                                               \
    do {                                                                               \
        std::ostringstream err;                                                        \
        err << msg;                                                                    \
        throw calcpp::Exception(err.str());                                            \
    } while (false)

#define THROW_NAME_ERROR(msg)   THROW_ERROR("NameError: " << msg)
#define THROW_SYNTAX_ERROR(msg) THROW_ERROR("SyntaxError: " << msg)
#define THROW_INVALID_SYNTAX_ERROR(str, index)                                         \
    THROW_ERROR(                                                                       \
        "\t" << str << "\n\t" << std::setfill(' ') << std::setw(index + 2) << "^\n"    \
             << "Syntax Error: invalid syntax");
#define THROW_TYPE_ERROR(msg)          THROW_ERROR("TypeError: " << msg)
#define THROW_VALUE_ERROR(msg)         THROW_ERROR("ValueError: " << msg)
#define THROW_UNIMPLEMENTED_ERROR(msg) THROW_ERROR("UnimplementedError: " << msg)
