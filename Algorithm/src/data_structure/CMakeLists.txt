## add all subdirs into include directories.
set(ALL_SUB_DIRS "")
file(GLOB ALL_SUB RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(sub_dir ${ALL_SUB})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${sub_dir})
        list(APPEND ALL_SUB_DIRS ${sub_dir})
        #include_directories(${sub_dir})
    endif()
endforeach()
list(APPEND ALL_SUB_DIRS .)

## add all source files into DATA_STRUCTURE_SRC_LIST. 
set(CURRENT_DIR_NAME algorithm)
set(DATA_STRUCTURE_SRC_LIST "")
foreach(sub ${ALL_SUB_DIRS})
    set(temp_src_dir "")
    aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/${sub} temp_src_dir)
    foreach(t ${temp_src_dir})
        #list(APPEND DATA_STRUCTURE_SRC_LIST ${t})
    endforeach()
endforeach()

file(GLOB_RECURSE CPP_LIST ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB_RECURSE C_LIST ${CMAKE_CURRENT_LIST_DIR}/*.c)
set(DATA_STRUCTURE_SRC_LIST
    ${CPP_LIST}
    ${C_LIST}
    )
