#include "include/apue.h"
#include "include/inc.h"

NS_BEGIN(elloop);

class FileDirectory {
public:

    static void run(int argc, char** argv) {
        printFileType(argc, argv);
    }

    static void printFileType(int argc, char** argv) {
        struct stat buf;
        for (int i=1; i<argc; ++i) {
            p(argv[i]); p(": ");
            if (lstat(argv[i], &buf) < 0) {
                err_ret("lstat error");
                continue;
            }
            if (S_ISREG(buf.st_mode)) {
                pln("regular");
            }
            else if (S_ISDIR(buf.st_mode)) {
                pln("directory");
            }
            else if (S_ISCHR(buf.st_mode)) {
                pln("character special");
            }
            else if (S_ISBLK(buf.st_mode)) {
                pln("block special");
            }
            else if (S_ISFIFO(buf.st_mode)) {
                pln("fifo");
            }
            else if (S_ISLNK(buf.st_mode)) {
                pln("symbolic link");
            }
            else if (S_ISSOCK(buf.st_mode)) {
                pln("socket");
            }
            else {
                pln("** unknown mode **");
            }
        }
    }
    
};

NS_END(elloop);
