#pragma once

#include <fstream>
#include <istream>
#include <memory>
#include <sstream>
#include <string>

namespace calcpp {

    typedef std::unique_ptr<std::istream> unique_istream;

    // open file stream inside unique pointer
    inline unique_istream open(const std::string& filename) {
        return std::make_unique<std::fstream>(filename);
    }

    // string to sstream inside unique pointer
    inline unique_istream sstream(const std::string& str) {
        return std::make_unique<std::istringstream>(str);
    }

    template<typename T>
    unique_istream& operator>>(unique_istream& in, T& t) {
        (*in) >> t;
        return in;
    }

}  // namespace calcpp
