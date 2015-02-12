_Pragma("once")

#include <iostream>
#include <string>
#include <cstdio>

namespace elloop {

#define psln(x) do { std::cout << #x " = " << (x) << std::endl; } while (0);
#define ps(x) do { std::cout << #x " = " << (x); } while (0);
#define	cr do { std::cout << std::endl; } while (0);

#define LOG(...)  do { \
                      fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);\
                      fprintf(stderr, __VA_ARGS__);\
                  } while (0);

#ifdef NDEBUG
#define DEBUG_LOG(...) 
#else
#define DEBUG_LOG(...)  LOG(__VA_ARGS__)
#endif


template <typename T>
inline void pc(const T & x) {
    std::cout << "************************" << x << "*********************";
}

template <typename T>
inline void pcln(const T & x) {
    std::cout << "************************" << x << "*********************" << std::endl;
}

template <typename T>
inline void p(const T & x) {
    std::cout << x;
}

template <typename T>
inline void pln(const T & x) {
    std::cout << x << std::endl;
}

/* template <typename T> */
/* inline void ps(const std::string & str, const T & x){ */
    /* std::cout << str << " = " << x; */
/* } */

/* template <typename T> */
/* inline void psln(const T & x){ */
    /* std::cout << _TEXT(x) << " = " << x << std::endl; */
/* } */

} // end namespace elloop;

