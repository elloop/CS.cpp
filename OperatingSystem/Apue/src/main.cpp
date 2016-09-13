#include "inc.h"
#include "inter_signal.h"
#include "file_io.h"
#include "file_directory.h"
#include "stdio_lib.h"
#include "ip_address.h"

#include <iostream>

using namespace elloop;

std::string FileIO::fileName_("/Users/elloop/codes/temp/apue/fileio-read.txt");

int main(int argc, char * argv[]) {
    // InterSignal::run(argc, argv);
    // FileIO::run(argc, argv);
    // FileDirectory::run(argc, argv);
    StdioLib::run(argc, argv);
    // IpAddress::run(argc, argv);
    return 0;
}

