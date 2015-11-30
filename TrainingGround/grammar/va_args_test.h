#pragma once
<<<<<<< HEAD

#include "inc.h"

NS_BEGIN(elloop);
NS_END(elloop);
=======
#include "inc.h"

NS_BEGIN(elloop);

// ------------------ using va_list ------------------
int vsum(int count, ...);

// ------------------ using template function. ------------------
template <typename T, typename ... Args>
T vsum1(const T &t, const Args&... args) {
    T sum(0);
    sum += t;
    sum += vsum1(args...);
    return sum;
}

template <typename T>
T vsum1(const T &t) { return t; }


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
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340
