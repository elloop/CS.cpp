message("adding lib: gtest......")
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src GTEST_SRC)
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_library(gtest ${GTEST_SRC})
