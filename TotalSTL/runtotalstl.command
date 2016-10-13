#! /bin/bash

CURR_FILE_NAME=`basename ${0}`
EXECUTABLE=total_stl

CUR_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd ${CUR_DIR}

log_from_me() {
    echo "[${CURR_FILE_NAME}] ${1}"
}

on_error_msg() {
    local retv=$?
    if [ $retv -gt 0 ]; then
        log_from_me $1
        read -n1 -r -p "[${CURR_FILE_NAME}] Press any key to continue..."
        exit 1
    fi
}

if [ "$1" = "r" ] || [ ! -d "build" ]; then
    if [ -d "build" ] ; then
        log_from_me "removing old build dir..."
        rm -rf ./build
        log_from_me "done"
    fi
    log_from_me "create build dir..."
    mkdir build
    cd ./build
    cmake ../
    on_error_msg "cmake failed"
    cp ./compile_commands.json ../src/
    log_from_me "cmake finish"
    cd ..
fi

cd build
make 

on_error_msg "make failed"

log_from_me "make finish"

cd ./bin  # make ./bin as cwd.

./${EXECUTABLE}

read -n1 -r -p "[${CURR_FILE_NAME}] Press any key to continue..."

exit 0;

