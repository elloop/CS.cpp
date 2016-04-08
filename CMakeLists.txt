cmake_minimum_required(VERSION 3.0)
project(CS_CPP)

include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(CXX_FLAGS
 -std=c++11
 -g
 -Wall
 -Wextra
 -Werror
 -Wno-unused-parameter
 -Wno-unused-variable
 -Wno-sign-compare
 # -Wno-format
 # -DCHECK_PTHREAD_RETURN_VALUE
 # -D_FILE_OFFSET_BITS=64
 # -Wconversion
 # -Wold-style-cast
 # -Woverloaded-virtual
 # -Wpointer-arith
 # -Wshadow
 # -Wwrite-strings
 # -march=native
 # -rdynamic
 # -DVALGRIND
 # -MMD
 )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(./include/gtest)
add_subdirectory(./Algorithm/src)
#add_subdirectory(./c_language/src)
#add_subdirectory(./TotalSTL/src)
#add_subdirectory(./TrainingGround/src)
#add_subdirectory(./UnderstandingCpp11/src)
#add_subdirectory(./util/src)


