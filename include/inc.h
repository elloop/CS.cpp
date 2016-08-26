#include "print_util.h"
#include "macro_define.h"
#include "gtest/gtest.h"
#include <cassert>
#include "noncopyable.h"

# if __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus >= 201103L
// Compiling in at least C++11 mode.
#  define CSCPP_LANG_CXX11 1
# else
#  define CSCPP_LANG_CXX11 0
# endif
