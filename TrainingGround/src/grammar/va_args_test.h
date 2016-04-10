#pragma once

#include "inc.h"

NS_BEGIN(elloop);

// ------------------ using va_list ------------------
int vsum(int count, ...);

// ------------------ using template function. ------------------

// added @20160410 for clang++ compile error: line22, no matching function for call to 'vsum1'
template <typename T, typename ... Args> T vsum1(const T &t, Args&... args);

template <typename T>
T vsum1(const T &t) { return t; }

template <typename T, typename ... Args>
T vsum1(const T &t, const Args&... args) {
    T sum(0);
    sum += t;
    sum += vsum1(args...);
    return sum;
}



// ------------------ using template class. ------------------
template <long ... Args> class vsum2;

template <long d, long ... Args>
class vsum2<d, Args...> {
public:
    static const long value = d + vsum2<Args...>::value;

    // optional 
    long operator () () const {
        return value;
    }
};

template <>
class vsum2<> {
public:
    static const long value = 0;

    // optional 
    long operator () () const {
        return value;
    }
};
NS_END(elloop);
