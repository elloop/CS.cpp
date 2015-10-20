#include "include/FileSystemTest.h"
#include "include/apue.h"
void testFileSystem(void) {
    writeFileWithHole();
}

void testSeekOffset(void) {
    if (-1 == lseek(STDIN_FILENO, 0, SEEK_CUR)) {
        printf("cannot seek stdin_fileno");
    }
    else {
        printf("seek stdin_fileno");
    }
}

void writeFileWithHole(void) {
    char    buf1[] = "abcdefg";
    char    buf2[] = "ABCDEFG";
    int     fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0) {
        err_sys("creat error");
    }

    if (write(fd, buf1, 7) != 7) {
        err_sys("write buf1 error");
    }

    if (-1 == lseek(fd, 16384, SEEK_SET)) {
        err_sys("lseek error");
    }

    if (write(fd, buf2, 7) != 7) {
        err_sys("write buf2 error");
    }

}

