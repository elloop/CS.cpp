set(LIBRARY_OUTPUT_PATH     ${PROJECT_BINARY_DIR}/lib)

message("in gtest cmake")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src GTEST_SRC)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(gtest ${GTEST_SRC})
