#pragma once

#include <fcntl.h>
#include "include/apue.h"
#include "include/inc.h"
#include <string>

NS_BEGIN(elloop);

class FileIO {
public:

    static std::string fileName_;

    static int run(int argc, char** argv) {
        // creatFile();
        // openFileRead();
        // openFileWrite();
        // canSeek();
        // createHoleFile();
        // copyFile();
        printFileFlag(argc, argv);
        return 0;
    }
    
    static bool creatFile() {
        const char* fileName = "/Users/elloop/codes/temp/apue/fileio-created.txt";
        // FILE_MODE = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
        int fd = creat(fileName, FILE_MODE);
        ERR_IF_NEG(fd, err_sys, "fail to creat %s", fileName);
        pv("create file %s succeed\n", fileName);
        close(fd);
        return true;
    }

    static bool openFileRead() {
        int fd = open(fileName_.c_str(), O_RDONLY);
        ERR_IF_NEG(fd, err_sys, "fail to open %s", fileName_.c_str());

        char buff[MAXLINE]; 
        while (read(fd, buff, MAXLINE) > 0) {
            printf("%s", buff);
        }
        close(fd);
        return true;
    }

    static void openFileWrite() {
        int fd = open(fileName_.c_str(), O_WRONLY);
        ERR_IF_NEG(fd, err_sys, "fail to open %s", fileName_.c_str());
        char buff[] = "===buff content===\n";

        // write to begin, default offset is SEEK_SET when file open mode is not O_APPEND.
        ERR_IF( write(fd, buff, strlen(buff)) != strlen(buff), err_sys, "fail to write buff");

        // goto end of file.
        ERR_IF(lseek(fd, 0, SEEK_END) == -1, err_sys, "fail to seek");

        ERR_IF( write(fd, buff, strlen(buff)) != strlen(buff), err_sys, "fail to write buff");

        pv("fileSize: %.2f k. \n", getFileSize(fd) / 1024.0);

        close(fd);
    }

    static off_t getFileSize(int fd) {
        off_t res(0);
        off_t cur = lseek(fd, 0, SEEK_CUR);
        ERR_IF(cur == -1, err_sys, "fail to seek");

        ERR_IF( lseek(fd, 0, SEEK_SET) == -1, err_sys, "fail to seek");

        res = lseek(fd, 0, SEEK_END);
        ERR_IF( res == -1, err_sys, "fail to seek");

        ERR_IF(lseek(fd, cur, SEEK_SET) == -1, err_sys, "fail to seek");

        return res;
    }

    static bool canSeek() {
        if ((lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1) {
            pln("can not seek");
            return false;
        }
        else {
            pln("can seek");
            return true;
        }
    }

    static void createHoleFile() {
        const char* holeFileName = "/Users/elloop/codes/temp/apue/file.hole";
        int fd = creat(holeFileName, FILE_MODE);
        ERR_IF_NEG(fd, err_sys, "fail to create : %s\n", holeFileName);

        char lower[] = "abcdefghijklmn";
        ERR_IF(write(fd, lower, strlen(lower)) != strlen(lower), err_sys, "lower write error");

        ERR_IF( lseek(fd, 16384, SEEK_SET) == -1, err_sys, "fail to seek");

        char upper[] = "ABCDEFGHIJKLMN";
        ERR_IF( write(fd, upper, strlen(upper)) != strlen(upper), err_sys, "upper, write error");

        close(fd);
    }

    static void copyFile() {
        int n;
        char buff[MAXLINE];
        while ((n = read(STDIN_FILENO, buff, MAXLINE)) > 0) {
            ERR_IF(write(STDOUT_FILENO, buff, n) != n, err_sys, "write error");
        }
        ERR_IF_NEG(n, err_sys, "read error");
    }

    static void printFileFlag(int argc, char** argv) {
        ERR_IF(argc != 2, err_quit, "usage: ./apuevim <descriptor#>");

        int val;
        int fd = std::stoi(argv[1]);
        ERR_IF((val = fcntl(fd, F_GETFL, 0)) < 0, err_sys, "fcntl error for fd %d", fd);

        switch (val & O_ACCMODE) {
            case O_RDONLY:
                p("read only");
                break;
            case O_WRONLY:
                p("write only");
                break;
            case O_RDWR:
                p("read write");
                break;
            default:
                err_dump("unknown access mode");
        }

        if (val & O_APPEND) {
            p(", append");
        }

        if (val & O_NONBLOCK) {
            p(", nonblocking");
        }

        if (val & O_SYNC) {
            p(", synchronous writes");
        }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
        if (val & O_FSYNC) {
            p(", synchronous writes");
        }
#endif
        cr;
    }

    static void setFL(int fd, int flags) {
        int val;
        ERR_IF((val = fcntl(fd, F_GETFL, 0)) < 0, err_sys, "fcntl F_GETFL error");
        val |= flags;
        ERR_IF(fcntl(fd, F_SETFL, val) < 0,err_sys, "fcntl F_SETFL error");
    }
    
    static void clrFL(int fd, int flags) {
        int val;
        ERR_IF((val = fcntl(fd, F_GETFL, 0)) < 0, err_sys, "fcntl F_GETFL error");
        val &= flags;
        ERR_IF(fcntl(fd, F_SETFL, val) < 0,err_sys, "fcntl F_SETFL error");
    }
};

NS_END(elloop);

