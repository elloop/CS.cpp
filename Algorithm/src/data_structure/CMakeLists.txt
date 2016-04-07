## add all subdirs into include directories.
set(ALL_SUB_DIRS "")
file(GLOB ALL_SUB RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(sub_dir ${ALL_SUB})
    #message("sub_dir: " ${sub_dir})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${sub_dir})
        #message("sub_dir is directory " ${sub_dir})
        list(APPEND ALL_SUB_DIRS ${sub_dir})
        include_directories(${sub_dir})
    endif()
endforeach()

## add all source files into DATA_STRUCTURE_SRC_LIST recursively.
set(CURRENT_DIR_NAME algorithm)
set(DATA_STRUCTURE_SRC_LIST "")
list(APPEND ALL_SUB_DIRS .)
foreach(sub ${ALL_SUB_DIRS})
    #message("searching src deal with : " ${sub})
    set(temp_src_dir "")
    aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/${sub} temp_src_dir)
    foreach(t ${temp_src_dir})
        #message("src found: " ${t})
        list(APPEND DATA_STRUCTURE_SRC_LIST ${t})
    endforeach()
endforeach()

foreach(s ${DATA_STRUCTURE_SRC_LIST})
    message("data_structure src: " ${s})
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


