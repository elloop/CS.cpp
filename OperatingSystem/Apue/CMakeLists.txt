cmake_minimum_required( VERSION 3.0)
project(apuevim)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR})

foreach(f ${SRC_FILES})
    message(${f})
endforeach()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
add_executable(${PROJECT_NAME} ${SRC_FILES})

