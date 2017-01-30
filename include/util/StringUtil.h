#pragma once

#include "inc.h"
#include <string>

# if !CSCPP_LANG_CXX11 
# error("__FILE__ should be compiled with at least c++11")
# endif

class StringUtil {
public:
    StringUtil() {
    }
    ~StringUtil() {
    }
    StringUtil(const StringUtil & other) = delete;
    StringUtil(StringUtil && moved) = delete;

    template <typename T>
    static std::string toString(const T &t) {
        return std::to_string(t);
    }

    static int stoi(const std::string &s, size_t* pos = 0, int base = 10) {
        return std::stoi(s, pos, base);
    }

    static long stol(const std::string &s, size_t* pos = 0, int base = 10) {
        return std::stol(s, pos, base);
    }

    static long long stoll(const std::string &s, size_t* pos = 0, int base = 10) {
        return std::stoll(s, pos, base);
    }


    static unsigned long stoul(const std::string &s, size_t* pos = 0, int base = 10) {
        return std::stoul(s, pos, base);
    }

    static unsigned long long stoull(const std::string &s, size_t* pos = 0, int base = 10) {
        return std::stoull(s, pos, base);
    }


    static float stof(const std::string &s, size_t* pos = 0) {
        return std::stof(s, pos);
    }

    static double stod(const std::string &s, size_t* pos = 0) {
        return std::stod(s, pos);
    }

    static long double stold(const std::string &s, size_t* pos = 0) {
        return std::stold(s, pos);
    }

    static std::string format(const char *fmt, ...) {
        va_list va;
        va_start(va, fmt);
        char *str = new char[1024];
        sprintf(str, fmt, va);
        std::string res(str);
        delete [] str;
        va_end(va);
        return res;
    }

};

