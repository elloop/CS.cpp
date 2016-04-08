set(ALL_SUB_DIRS "")
file(GLOB ALL_SUB RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(sub_dir ${ALL_SUB})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${sub_dir})
        list(APPEND ALL_SUB_DIRS ${sub_dir})
        include_directories(${sub_dir})
    endif()
endforeach()
list(APPEND ALL_SUB_DIRS .) # also include current dir.

## add all source files into ALGORITHM_SRC_LIST. assume that the depth of the sub dir is 2 at most.
set(CURRENT_DIR_NAME algorithm)
set(ALGORITHM_SRC_LIST "")
foreach(sub ${ALL_SUB_DIRS})
    set(temp_src_dir "")
    aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/${sub} temp_src_dir)
    foreach(t ${temp_src_dir})
        list(APPEND ALGORITHM_SRC_LIST ${t})
    endforeach()
endforeach()

