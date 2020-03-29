#pragma once

#include <exception>
#include <sstream>
#include <string>

struct Exception: std::exception {
    
    std::string msg;

    template <typename...Args>
    Exception(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        msg = oss.str();
    }

    Exception& operator=(const Exception& other) noexcept {
        this->msg = other.msg;
        return *this;
    }

    virtual const char * what () const noexcept override {
        return msg.c_str();
    }

};

