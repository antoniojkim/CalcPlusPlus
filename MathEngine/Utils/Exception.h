#pragma once

#ifndef __UTILS_EXCEPTIONS_H__
#define __UTILS_EXCEPTIONS_H__

#include <exception>
#include <sstream>
#include <string>
#include <utility>

struct Exception: std::exception {

    std::string msg;

    template <typename... Args>
    Exception(Args&&... args) {
        std::ostringstream out;
        print(out, std::forward<Args>(args)...);
        msg = out.str();
    }

    Exception& operator=(const Exception& other) noexcept {
        this->msg = other.msg;
        return *this;
    }

    virtual const char * what () const noexcept override {
        return msg.c_str();
    }


    static std::ostream& print(std::ostream& out) { return out; }

    template <typename T, typename... Args>
    static std::ostream& print(std::ostream& out, T t, Args... args)
    {
        out << t;
        return print(out, args...);
    }

};

std::ostream& operator<<(std::ostream& out, const Exception& e);

#endif // __UTILS_EXCEPTIONS_H__
