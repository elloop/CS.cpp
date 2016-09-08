#include "print_util.h"
#include "macro_define.h"
#include <cassert>
#include "noncopyable.h"

# ifndef APUE
#   include "gtest/gtest.h"
# endif

# if __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus >= 201103L
// Compiling in at least C++11 mode.
#  define CSCPP_LANG_CXX11 1
# else
#  define CSCPP_LANG_CXX11 0
# endif

# ifdef APUE
#   define ERR_IF_NEG(N, _ERR_FUNC_,  ...) do { \
            if ((N) < 0) {                     \
                _ERR_FUNC_(__VA_ARGS__);       \
            }                                  \
        } while(0);

#   define ERR_IF(cond, _ERR_FUNC_, ...) do { \
            if ((cond)) {                      \
                _ERR_FUNC_(__VA_ARGS__);       \
            }                                  \
        } while(0);
# endif
