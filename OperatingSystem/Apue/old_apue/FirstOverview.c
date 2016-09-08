#include "include/FirstOverview.h"
#include "include/apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // EACCES
#include <dirent.h>

void ls(char* dirStr) {
    DIR 	        *dp;
    struct dirent   *dirp;

    if ((dp = opendir(dirStr)) == NULL) {
        err_sys("can't open %s", dirStr);
    }
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }

    closedir(dp);
}

void copyWithSysApi(void) {
#define BUFFSIZE 4096
    int     n;
    char    buf[BUFFSIZE];

    while ((n=read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) !=n ) {
            err_sys("write error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }
}

void copyWithStandIO(void) {
    int     c = 0;
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            err_sys("output error");
        }
    }

    if (ferror(stdin)) {
        err_sys("input error");
    }

}

void simpleShell(void) {
    char        buff[MAXLINE];
    pid_t       pid;
    int         status = 0;

    printf("%% ");
    while (fgets(buff, MAXLINE, stdin) != NULL) {
        if ('\n' == buff[strlen(buff) - 1]) {
            buff[strlen(buff) - 1] = 0;
        }

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        }
        else if (pid == 0) {
            execlp(buff, buff, (char*)0);
            err_ret("couldn't execute : %s", buff);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error");
        }
        printf("%% ");
    }
}

void overviewTest(int argc, char* argv[]) {

    printf("uid = %d, gid = %d\n", getuid(), getgid());

    printf("uid = %d \n", getpid());

    // test error no.
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;
    errno = EACCES;
    perror(argv[0]);


    if (argc > 1) {
        pc("ls");
        ls(argv[1]);
    }

    /* pc("copyWithSysApi"); */
    /* copyWithSysApi(); */

    /* pc("copyWithStandIO"); */
    /* copyWithStandIO(); */

    pc("simpleShell");
    simpleShell();

}


