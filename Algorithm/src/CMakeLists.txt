set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)

## function definition: INCLUDE_SUB_DIRECTORIES_RECURSIVELY
function(INCLUDE_SUB_DIRECTORIES_RECURSIVELY root_dir)

    if (IS_DIRECTORY ${root_dir})
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            INCLUDE_SUB_DIRECTORIES_RECURSIVELY(${root_dir}/${sub})
        endif()
    endforeach()
endfunction()


include(algorithm/CMakeLists.txt)
include(bigword/CMakeLists.txt)
include(data_structure/CMakeLists.txt)

set(SRC_LIST
    main.cpp
    ${ALGORITHM_SRC_LIST}
    ${BIGWORD_SRC_LIST}
    ${DATA_STRUCTURE_SRC_LIST}
    )

foreach(src ${SRC_LIST})
    message("Algorithm src: " ${src})
endforeach()

add_executable(algorithm ${SRC_LIST})

include_directories(.)
link_directories(${PROJECT_BINARY_DIR}/lib)

set(LINK_LIBS
   gtest
#    util.a
    )

target_link_libraries(algorithm ${LINK_LIBS})



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
