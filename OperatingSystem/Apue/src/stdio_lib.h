#pragma once

#include "include/apue.h"
#include "include/inc.h"

// #include <cstdio>

#include <stdio.h>

NS_BEGIN(elloop);

class StdioLib {
public:

    static int run(int argc, char** argv) {
        // printBufferType();
        // tmpnameTest();
        // mkstempTest();

        return 0;
    }

# if defined(linux)
    static void memopenTest() {
        const int kBufSize = 48;
        char buf[kBufSize];

        memset(buf, 'a', kBufSize - 2);
        buf[kBufSize - 2] = 0;
        buf[kBufSize - 1] = 'X';
        ERR_IF(fmemopen(buf, kBufSize, "w+") == NULL, err_sys, "fail to call fmemopen");
        pv("initial content of buf: %s\n", buf);
        fprintf(fp, "hello world");
        fflush(fp);
        pv("after flush: %s\n", buf);
        pv("length of buf: %ld\n", (long)strlen(buf));

        memset(buf, 'b', kBufSize - 2);
        buf[kBufSize - 2] = 0;
        buf[kBufSize - 1] = 'X';
        fprintf(fp, "hello, world");
        fseek(fp, 0, SEEK_SET);
        pv("after seek, buf is: %s\n", buf);
        pv("length of buf is: %ld\n", (long)strlen(buf));

        memset(buf, 'c', kbufsize - 2);
        buf[kBufSize - 2] = 0;
        buf[kBufSize - 1] = 'X';
        fprintf(fp, "hello world");
        fclose(fp);
        pv("after close, buf is: %s\n", buf);
        pv("length of buf is : %ld\n", (long)strlen(buf));
    }
# endif

    static void mkstempTest() {
        auto makeTemp = [] (char* tmplate) {
            int fd;
            fd = mkstemp(tmplate);
            ERR_IF(fd < 0, err_sys, "fail to create temp file");
            close(fd);
            struct stat statBuf;
            if (stat(tmplate, &statBuf) < 0) {
                if (ENOENT == errno) {
                    pln("file don't exist");
                }
                else {
                    err_sys("stat failed");
                }
            }
            else {
                pln("file exist");
                unlink(tmplate);
            }
        };

        char goodTemplate[] = "/tmp/dirXXXXXX";
        char* badTemplate = "/tmp/dirXXXXXX";
        pln("trying to create first temp file");
        makeTemp(goodTemplate);
        pln("trying to create second temp file");
        makeTemp(badTemplate);  // will fail.
    }

    /*
     * tmpnam, tmpfile return NULL on fail.
     *
     */
    static void tmpnameTest() {
        char* tmpN = tmpnam(NULL);
        pv("first tmpname: %s\n", tmpN ? tmpN : "NULL");
        char t[L_tmpnam];
        pv("second tmpname: %s\n", tmpnam(t) ? t : "NULL");
        // pv("t is %s\n", t ? t : "NULL"); // address of array t will always evaluate to true.

        // test tmpfile
        FILE* tmp = tmpfile();
        ERR_IF(tmp == NULL, err_sys, "fal to create tmpfile()");
        fputs("something input into tmpfile", tmp);
        rewind(tmp);
        char oneline[MAXLINE];
        ERR_IF(fgets(oneline, sizeof(oneline), tmp) == NULL, err_sys, "fail to fgets temp");
        pv("read back from tmp: %s\n", oneline);
        sleep(15);
        pln("done");
    }

    static void printStdio(const char* name, FILE* fp) {
        pv("stream: %s, ", name);
        if (isUnbuffered(fp)) {
            p("unbuffered");
        }
        else if (isLineBuffered(fp)) {
            p("line buffered");
        }
        else {
            p("fully buffered");
        }
        pv(", buffer size = %d\n", bufferSize(fp));
    }

#   if defined(_IO_UNBUFFERED)

    static int isUnbuffered(FILE* fp) {
        p("defined _IO_UNBUFFERED, ");
        return (fp->_flags & _IO_UNBUFFERED);
    }

    static int isLineBuffered(FILE* fp) {
        return (fp->_flags & _IO_LINE_BUF);
    }

    static int bufferSize(FILE* fp) {
        return (fp->_IO_buf_end - fp->_IO_buf_base);
    }

#   elif defined(__SNBF)

    static int isUnbuffered(FILE* fp) {
        p("defined __SNBF, ");
        return (fp->_flags & __SNBF);
    }

    static int isLineBuffered(FILE* fp) {
        return (fp->_flags & __SNBF);
    }

    static int bufferSize(FILE* fp) {
        // return (fp->_lbfsize);
        return (fp->_bf._size);
    }
    
#   elif defined(_IONBF)
#       ifdef _LP64
#           define _flag    __pad[4]
#           define _ptr     __pad[1];
#           define _base    __pad[2];
#       endif
    static int isUnbuffered(FILE* fp) {
        p("defined _IONBF, ");
        return (fp->_flag & _IONBF);
    }

    static int isLineBuffered(FILE* fp) {
        return (fp->_flags & _IONBF);
    }

    static int bufferSize(FILE* fp) {
#   ifdef _LP64
        return (fp->_base - fp->_ptr);
#   else
        return (BUFSIZE); // guess.
#   endif
    }

#   else
#       error unkown stdio implementation.
#   endif

    /*
     *
     *
     *
     * sample output:
     *
     *         input some character
     *         hellooo
     *         one line to standard error
     *         stream: stdin, defined __SNBF, fully buffered, buffer size = 4096
     *         stream: stdout, defined __SNBF, fully buffered, buffer size = 4096
     *         stream: stderr, defined __SNBF, unbuffered, buffer size = 1
     *         stream: /etc/passwd, defined __SNBF, fully buffered, buffer size = 4096
     *
     * notice: in some system, stdin and stdout is line buffered default.
     */
    static void printBufferType() {
        FILE* fp;

        fputs("input some character\n", stdout);
        ERR_IF(getchar() == EOF, err_sys, "fail to getchar");
        fputs("one line to standard error\n", stderr);

        printStdio("stdin", stdin);
        printStdio("stdout", stdout);
        printStdio("stderr", stderr);

        ERR_IF((fp = fopen("/etc/passwd", "r")) == NULL, err_sys, "fopen /etc/passwd error");
        ERR_IF(getc(fp) == EOF, err_sys, "getc error for /etc/passwd");
        printStdio("/etc/passwd", fp);
    }

};

NS_END(elloop);

