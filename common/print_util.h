_Pragma("once")

#include <iostream>
#include <string>
#include <cstdio>

namespace elloop {

#define psln(x) do { std::cout << #x " = " << (x) << std::endl; } while (0);
#define ps(x) do { std::cout << #x " = " << (x); } while (0);
#define	cr do { std::cout << std::endl; } while (0);

#define __VLOGD(...)  do { \
                      fprintf(stdout, "%s:%d: ", __FILE__, __LINE__);\
                      fprintf(stdout, __VA_ARGS__);\
                  } while (0);

#define __LOGD(...)  do { \
                      fprintf(stdout, __VA_ARGS__);\
                  } while (0);


#ifdef NDEBUG
#define LOGD(...) 
#else
#define LOGD(...)  __LOGD(__VA_ARGS__)
#endif

#ifdef NDEBUG
#define VLOGD(...) 
#else
#define VLOGD(...)  __VLOGD(__VA_ARGS__)
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

