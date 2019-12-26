#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <list>
#include <string>
#include <sstream>

std::list<std::string> split(const std::string& str, const char& delimiter){
    std::list<std::string> strList;
    std::istringstream iss{str};

    std::ostringstream oss;
    unsigned int size = 0;
    char c;
    while (iss.get(c)) {
        if (c == delimiter && size > 0) {
            strList.emplace_back(oss.str());
            oss.str("");
            oss.clear();
            size = 0;
        } else {
            oss << c;
            ++size;
        }
    }
    if (size > 0) {
        strList.emplace_back(oss.str());
    }

    return strList;
}

template<template<class> class Iterable>
std::string join(const Iterable<std::string>& str, const char& delimiter){
    std::ostringstream out;
    bool first = true;
    for (auto& s : str){
        if (!first){
            out << delimiter;
        }
        else{
            first = false;
        }
        out << s;
    }
    return out.str();
}

#endif // __STRING_UTILS_H__
