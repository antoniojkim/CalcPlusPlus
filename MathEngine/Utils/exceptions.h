#ifndef __UTILS_EXCEPTIONS_H__
#define __UTILS_EXCEPTIONS_H__

#include <sstream>
#include <string>

struct Exception {
    
    std::ostringstream err;
    std::string msg;

    template <class T>
    Exception(T arg) {
        err << arg;
        msg = err.str();
    }
    template <class T, class... T2>
    Exception(T arg, T2... args) {
        err << arg;
        Exception(args...);
    }

    const char * what () const throw () {
        return msg.c_str();
    }

};

#endif // __UTILS_EXCEPTIONS_H__
