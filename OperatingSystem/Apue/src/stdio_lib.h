#pragma once

#include "include/apue.h"
#include "include/inc.h"

NS_BEGIN(elloop);

class StdioLib {
public:

    static int run(int argc, char** argv) {
        printBufferType();
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

