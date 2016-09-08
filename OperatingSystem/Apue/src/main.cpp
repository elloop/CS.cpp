#include <iostream>
#include "inter_signal.h"
#include "file_io.h"
#include "file_directory.h"

using namespace elloop;

std::string FileIO::fileName_("/Users/elloop/codes/temp/apue/fileio-read.txt");

int main(int argc, char * argv[]) {
    // InterSignal::run(argc, argv);
    // FileIO::run(argc, argv);
    FileDirectory::run(argc, argv);
    return 0;
}

