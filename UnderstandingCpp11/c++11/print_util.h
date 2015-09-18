#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER


#include <iostream>
#include <string>
#include <cstdio>

namespace elloop {

#define psln(x) do { \
					std::cout << #x " = " << (x) << std::endl; \
				} while (0);
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
    std::cout << "************************" << x << "*********************" 
			  << std::endl;
}

template <typename T>
inline void p(const T & x) {
    std::cout << x;
}

template <typename T>
inline void pln(const T & x) {
    std::cout << x << std::endl;
}

template <typename T, size_t N>
void print_array(const T (& a)[N]) {
  std::cout << "length:" << N << ", (";
  for (size_t i=0; i<N; ++i) {
    std::cout << a[i];
    if (i < N - 1) {
      std::cout << ", ";
    }
  }
  std::cout << ")" << std::endl;
}

template <typename Con>
void print_container(const Con & c) {
  auto iter = c.begin();
  p("size: ");
  pln(c.size());
  p("(");
  std::string sep("");
  while (iter != c.end()) {
    p(sep);
    p(*iter);
    sep = ", ";
    ++iter;
  }
  pln(")");
}


/*
template <typename T, size_t N>
void print_array<T*, N>(const T (&a)[N]) {
  std::cout << "length:" << N << ", (";
  for (size_t i=0; i<N; ++i) {
    std::cout << a[i];
    if (i < N - 1) {
      std::cout << ", ";
    }
  }
  std::cout << ")" << std::endl;

}
*/

/* template <typename T> */
/* inline void ps(const std::string & str, const T & x){ */
    /* std::cout << str << " = " << x; */
/* } */

/* template <typename T> */
/* inline void psln(const T & x){ */
    /* std::cout << _TEXT(x) << " = " << x << std::endl; */
/* } */

} // end namespace elloop;

