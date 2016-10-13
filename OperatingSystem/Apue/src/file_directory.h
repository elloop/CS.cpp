#pragma once

#include "include/apue.h"
#include "inc.h"
#include <fcntl.h>
#include <sys/time.h> // utimes, futimes

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

NS_BEGIN(elloop);

class FileDirectory {
public:

    static void run(int argc, char** argv) {
        // printFileType(argc, argv);
        // accessTest(argc, argv);
        // umaskTest();
        // chmodTest();
        // testUnlink();
        // futimesTest();
        // chdirTest();
        // getcwdTest();
        printDeviceType(argc, argv);
    }

    /*
     * you can run this with following args on macOS.
     * ./apue / /Users/elloop /dev/tty /dev/ttyp[01234]
     *
     * explanation of major and minor macros are here: http://man7.org/linux/man-pages/man3/major.3.html
     * they are included in <sys/sysmacros.h> according to the man page, but i can't find it on my macOS.
     *
     */
    static void printDeviceType(int argc, char** argv) {
        int i(0);
        while (argv[i] != NULL) {
            pv("%s: ", argv[i]);
            struct stat statBuf;
            if (stat(argv[i], &statBuf) < 0) {
                err_ret("fail to stat: %s", argv[i]);
                continue;
            }
            pv("dev = %d/%d", major(statBuf.st_dev), minor(statBuf.st_dev));

            if (S_ISCHR(statBuf.st_mode) || S_ISBLK(statBuf.st_mode)) {
                pv("(%s) rdev=%d/%d", S_ISCHR(statBuf.st_mode) ? "character" : "block", major(statBuf.st_rdev), minor(statBuf.st_rdev));
            }
            cr;
            ++i;
        }
    }

    static void getcwdTest() {
        ERR_IF_NEG(chdir("/Users/elloop/codes"), err_sys, "fail to chdir to codes");
        // char* ptr;
        // int size;
        const int size = 100;
        char ptr[size];
        // ptr = path_alloc(&size);
        ERR_IF(getcwd(ptr, size) == NULL, err_sys, "getcwd failed");
        pv("cwd=%s\n", ptr);
    }

    static void chdirTest() {
        ERR_IF_NEG(chdir("/tmp"), err_sys, "fail to chdir to /tmp");
        pln("chdir to /tmp success");
    }

    /*
     * need foo for test.
     * ls -lu # time won't change (utime)
     * ls -l  # time won't change also(atime)
     * ls -lc # time will change (ctime i-node changed when program run.)
     *
     * maybe some error in apue page-101~102, futimens and utimensat don't exist on macOS
     */
    static void futimesTest() {
        struct stat statBuf;
        ERR_IF_NEG(stat("foo", &statBuf), err_sys, "fail to stat foo");

        int fd = open("foo", O_RDWR | O_TRUNC);
        ERR_IF_NEG(fd, err_sys, "fail to open foo for O_RDWR and O_TRUNC");

        struct timeval amTime[2];

        amTime[0].tv_sec = statBuf.st_atime;   // access time.
        amTime[0].tv_usec = 0;

        amTime[1].tv_sec = statBuf.st_mtime;   // content modification time.
        amTime[1].tv_usec = 0;

        ERR_IF_NEG(futimes(fd, amTime), err_sys, "fail to futimes for foo");
        close(fd);
    }
    /*
     * typical useage of unlink is to create a temp file in process, then after useing it
     * immediatly unlink it, after the process exit, the content of temp file will be delete.
     *
     */
    static void testUnlink() {
        ERR_IF_NEG(open("foo", O_RDWR), err_sys, "fail to open file foo");
        ERR_IF_NEG(unlink("foo"), err_sys, "fail to unlink foo");
        pln("foo unlinked");
        sleep(15);
        pln("done");
    }

    static void chmodTest() {
        struct stat statBuf;

        ERR_IF_NEG(stat("foo", &statBuf), err_sys, "stat error for foo");
        statBuf.st_mode |= S_ISGID;
        statBuf.st_mode &= ~S_IRGRP;
        ERR_IF_NEG(chmod("foo", statBuf.st_mode), err_sys, "fail to chmod for foo");

        ERR_IF_NEG(chmod("bar", S_IRUSR | S_IRGRP | S_IXOTH), err_sys, "fail to chmod for bar");
    }

    /*
     *
     * todo: use doxygen to format the comment and then extract as programming notes.
     * umask -S # show human readable mask in shell.
     *
     */
    static void umaskTest() {
        umask(0);
        ERR_IF(creat("foo", RWRWRW) < 0, err_sys, "fail to create foo");
        umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        ERR_IF(creat("bar", RWRWRW) < 0, err_sys, "fail to create bar");

    }

    static void accessTest(int argc, char** argv) {
        int i = 10;
        i /= 0;
        ERR_IF(argc != 2, err_quit, "usage: apue <pathname>");
        if (access(argv[1], R_OK) < 0) {
            err_ret("access error for %s", argv[1]);
        }
        else {
            pln("read access OK");
        }

        if (open(argv[1], O_RDONLY) < 0) {
            err_ret("open error for %s", argv[1]);
        }
        else {
            pln("open for reading ok");
        }
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
