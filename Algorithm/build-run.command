#! /bin/bash

CUR_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd ${CUR_DIR}

on_error_msg() {
    local retv=$?
    if [ $retv -gt 0 ]; then
        echo $1
        read -n1 -r -p "Press any key to continue..."
        exit 1
    fi
}

if [ "$1" = "r" ] || [ ! -d "build" ]; then
    # check build dir.
    if [ -d "build" ] ; then
        echo "removing old build dir..."
        rm -rf ./build
        echo "done"
    fi

    echo "create build dir..."
    mkdir build

    cd ./build

    cmake ../
    on_error_msg "cmake failed"
    echo "cmake finish"
fi

cd build

make 

on_error_msg "make failed"

echo "make finish"

cd ./bin

./algorithm

read -n1 -r -p "Press any key to continue..."

exit 0;

