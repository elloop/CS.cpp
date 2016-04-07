set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH     ${PROJECT_BINARY_DIR}/lib)

include(algorithm/CMakeLists.txt)
include(bigword/CMakeLists.txt)
include(data_structure/CMakeLists.txt)

set(SRC_LIST
    main.cpp
    ${ALGORITHM_SRC_LIST}
    ${BIGWORD_SRC_LIST}
    ${DATA_STRUCTURE_SRC_LIST}
    )

message("srcs: " ${SRC_LIST})
#add_executable(algorithm ${SRC_LIST})

#include_directories(${PROJECT_SOURCE_DIR}/../include)
#link_directories(${PROJECT_SOURCE_DIR}/../libs)

#set(LINK_LIBS
#   gtest.a
#    util.a
#    )

#target_link_libraries(algorithm ${LINK_LIBS})



################################################################################
#### step 1 : search source files.
# file(GLOB_RECURSE SRC_LIST "*.cpp")
#### step 2 : set search path
#### step 3 : set library search path
#### step 4 : link libraries.
#### step 5 : executable

# PROJECT_SOURCE_DIR value is the root directory which contain CMakeLists.txt that is passed to cmake.
# message("project binary dir" ${PROJECT_BINARY_DIR})
# message("project source dir in src/CMakeLists: " ${PROJECT_SOURCE_DIR})
