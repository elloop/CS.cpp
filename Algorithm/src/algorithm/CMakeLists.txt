include_sub_directories_recursively(${CMAKE_CURRENT_LIST_DIR})
#include_all_sources_recursively(ALGORITHM_SRC_LIST ${CMAKE_CURRENT_LIST_DIR})


# skip astar-2016 and oj folders.

include_all_sources_recursively(array_src ${CMAKE_CURRENT_LIST_DIR}/array)
include_all_sources_recursively(DP_src ${CMAKE_CURRENT_LIST_DIR}/DP)
include_all_sources_recursively(leetcode_src ${CMAKE_CURRENT_LIST_DIR}/leetcode)
include_all_sources_recursively(string_src ${CMAKE_CURRENT_LIST_DIR}/string)
include_all_sources_recursively(suffix_expression_src ${CMAKE_CURRENT_LIST_DIR}/suffix_expression)

set(ALGORITHM_SRC_LIST ${array_src} ${DP_src} ${leetcode_src} ${string_src} ${suffix_expression_src} )
