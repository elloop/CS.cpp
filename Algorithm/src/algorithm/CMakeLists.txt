## add all subdirs into include directories.
set(ALL_SUB_DIRS "")

#message("CMAKE_CURRENT_LIST_DIR: " ${CMAKE_CURRENT_LIST_DIR})
#message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB ALL_SUB RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(sub_dir ${ALL_SUB})
    #message("sub_dir: " ${sub_dir})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${sub_dir})
        #message("sub_dir is directory " ${sub_dir})
        list(APPEND ALL_SUB_DIRS ${sub_dir})
        include_directories(${sub_dir})
    endif()
endforeach()

## add all source files into ALGORITHM_SRC_LIST recursively.
set(CURRENT_DIR_NAME algorithm)
set(ALGORITHM_SRC_LIST "")
list(APPEND ALL_SUB_DIRS .)
foreach(sub ${ALL_SUB_DIRS})
    #message("searching src deal with : " ${sub})
    set(temp_src_dir "")
    aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/${sub} temp_src_dir)
    foreach(t ${temp_src_dir})
        #message("src found: " ${t})
        list(APPEND ALGORITHM_SRC_LIST ${t})
    endforeach()
endforeach()

foreach(s ${ALGORITHM_SRC_LIST})
    message("algorithm src: " ${s})
endforeach()









################################################################################################################
#MACRO(SUBDIRLIST result curdir)
#FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
#  SET(dirlist "")
#  FOREACH(child ${children})
#    IF(IS_DIRECTORY ${curdir}/${child})
#        LIST(APPEND dirlist ${child})
#    ENDIF()
#  ENDFOREACH()
#  SET(${result} ${dirlist})
#ENDMACRO()

