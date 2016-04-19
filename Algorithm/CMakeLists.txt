cmake_minimum_required ( VERSION 3.0)
project                ( algorithm)

# export compilation_database for YouCompleteMe Plugin in VIM.
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub})
        endif()
    endforeach()
endfunction()

function(include_all_sources_recursively target_list root_dir)
    file(GLOB_RECURSE cpp_list ${root_dir}/*.cpp)
    file(GLOB_RECURSE c_list ${root_dir}/*.c)
    set(${target_list} ${cpp_list} ${c_list} ${hearder_list} PARENT_SCOPE)
endfunction()

include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(${PROJECT_SOURCE_DIR}/../include)

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

set(CMAKE_CXX_COMPILER      "clang++" )
set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG " )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../build/${PROJECT_NAME}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/../build/${PROJECT_NAME}/lib)

include_directories ( ${PROJECT_SOURCE_DIR}/src)
link_directories    ( ${LIBRARY_OUTPUT_PATH})

include(${PROJECT_SOURCE_DIR}/../include/gtest/CMakeLists.txt)   # build libgtest.a
include(${PROJECT_SOURCE_DIR}/src/algorithm/CMakeLists.txt)      # ALGORITHM_SRC_LIST      defined here
include(${PROJECT_SOURCE_DIR}/src/bigword/CMakeLists.txt)        # BIGWORD_SRC_LIST        defined here
include(${PROJECT_SOURCE_DIR}/src/data_structure/CMakeLists.txt) # DATA_STRUCTURE_SRC_LIST defined here

set(SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${ALGORITHM_SRC_LIST}
    ${BIGWORD_SRC_LIST}
    ${DATA_STRUCTURE_SRC_LIST}
    )

foreach(src ${SRC_LIST})
    message("algorithm src: " ${src})
endforeach()

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(LINK_LIBS gtest)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})
