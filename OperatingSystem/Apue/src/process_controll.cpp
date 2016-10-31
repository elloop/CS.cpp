/*
 * error committed:
 *
 *      1. use int as pid type. 
 *          should be pid_t.
 *
 *      2. use (pid>0) as the fork() and vfork() return value to the child process.
 *          should be (pid == 0) to the child process.
 *
 *      3. use getpid() to get parent pid in Waitpid test case.
 *          should use getppid().
 *
 *      4. RaceCondition test case, don't act as book say. there is no intermixing of output from the two processes.
 *          should be tested in single core cpu machine.
 *
 *      PS: 今天升级系统到macOS Sierra，发现/usr/include/ 文件夹消失了。经过一番搜索才了解到这样一个事实：要在macOS上programming，需要安装Xcode（或至少是toolchain）。
 *          这才了解到原来macOS默认是不提供POSIX环境的，比如我include <unistd.h> 都提示找不到，与之类似的POSIX要求提供的header files都需要安装Xcode才能使用。
 *          于是：`xcode-select --install`安装上toolchain之后，发现/usr/include/ 目录出现了，同时unistd.h 等header files也都出现了。
 */

/*
 * questions:
 *
 *  1. in case `System`, why _exit(127) in child process, does execl() has no return value if it fail ?
 *      
 *      `man system` : ISO C system function return when shell exec fail.
 *
 *  2. does `system(const char *cmd)` conflict with the function `system` defined in <stdlib.h>?
 *  
 *      local system(...) will hide ISO system(...), use std::system(...) to call the std version explicitly.
 *
 *  3. what value is `ret` set for in watpid(pid, &ret, 0) ? Is ret equal to the return value of the child process?
 *      ret stores the termination status of the terminated process. 
 *      its value is defined by implementation. with certain bits indicating the exit status, other bits indicating the signal number and one bit indicating whether a 
 *      core file is generated, and so on. use the macro defined in <sys/wait.h> to check it. see printExit() function defined below.
 *
 */

#include "include/inc.h"
#include "include/apue.h"
// #include <cstdlib>   // if you use ISO C system 
#include <sys/time.h>
#include <cassert>
#include <sys/times.h>
#include <string>
#include <vector>
#include <dirent.h>

using namespace std;
using std::string;

NS_BEGIN(elloop);


int globalVar = 100;
// demonstrate sub-process holds a copy of parent process.
// ****************************************************************************
BEGIN_TEST(ProcessControll, Fork, @@);

string buff("content from buff\n");

int localV = 1;
ERR_IF(write(STDOUT_FILENO, buff.c_str(), buff.length()) != buff.length(), err_ret, "fail to write buff");

// pv("before fork!");
pv("before fork!\n");    // \n will flush stdout.

// fflush(STDOUT_FILENO);       // fflush(FILE*), not fd.
// fflush(stdout);              // flush stdout so the "before fork" won't be copied into sub-process.

pid_t pid(0);
if ((pid = fork()) < 0) {
    err_sys("fail to fork");
}
else if (pid == 0) {
    // child process.
    ++globalVar;
    ++localV;
}
else {
    // > 0, parent process.
    sleep(2);
}

pv("pid: %ld, globalVar: %d, localV: %d\n", (long)getpid(), globalVar, localV);

END_TEST;


// ****************************************************************************
int globalVar2 = 10;
BEGIN_TEST(ProcessControll, Vfork, @@);

int localV = 1;
pv("before vfork!\n");
pid_t pid(0);
if ((pid = vfork() ) < 0) {
    err_sys("fail to vfork");
}
else if (pid == 0) {
    // child
    ++globalVar2;
    ++localV;
    _exit(0);
    // exit(0);        // 60338 Segmentation fault: 11
}

pv("pid: %ld, globalVar2: %d, localV: %d\n", (long)getpid(), globalVar2, localV);
// pid: 60416, globalVar2: 11, localV: 2

END_TEST;


// ****************************************************************************
void printExit(int status) {
    if (WIFEXITED(status)) {
        pv("normal termination, exit status = %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        pv("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ?  " (core file generated)" : "");
#else
                "");
#endif
    }
    else if (WIFSTOPPED(status)) {
        pv("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

BEGIN_TEST(ProcessControll, ExitStatus, @@);

pid_t pid;
int st;

pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (pid == 0) {
    exit(7);
}
ERR_IF(wait(&st) != pid, err_sys, "wait error");
printExit(st);

pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (pid == 0) {
    abort();
}
ERR_IF(wait(&st) != pid, err_sys, "wait error");
printExit(st);


pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (0 == pid) {
    st /= 0;
}
ERR_IF(wait(&st) != pid, err_sys, "wait error");
printExit(st);

END_TEST;

// ****************************************************************************
BEGIN_TEST(ProcessControll, Waitpid, @@);

pid_t pid;
pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (0 == pid) {
    // first child
    pid = fork();
    ERR_IF_NEG(pid, err_sys, "fail to fork");
    if (pid > 0) {
        exit(0);    // first child terminate.
    }

    // second child continuing... will be inherited by init process.
    sleep(2);
    pv("parent pid: %ld\n", (long)getppid());
    exit(0);
}

// parent process, wait for the first child.
ERR_IF(waitpid(pid, NULL, 0) != pid, err_sys, "waitpid error");     // NULL means don't care about the termination status of the child process.
exit(0);

END_TEST;


// todo: run this case on a single core cpu machine.
// ****************************************************************************
BEGIN_TEST(ProcessControll, RaceCondition, @@);

auto printChar = [](char* str) {
    char*   ptr;
    int     c;
    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) !=0; ) {
        putc(c, stdout);
    }
};

pid_t pid;
pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (0 == pid) {
    printChar("print char in child process\n");
}
else {
    printChar("print char in parent process\n");
}

END_TEST;


// add `echoall` path into path before run this case.
// export PATH=$PATH:/Users/elloop/codes/temp/
// ****************************************************************************
BEGIN_TEST(ProcessControll, Exec, @@);

pid_t pid;
pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");

const char    *envInit[] = {"USER=nonono", "PATH=/tmp", NULL};
if (0 == pid) {
    int ret = execle("/Users/elloop/codes/temp/echoall", "echoall-elloop", "arg1", "arg-2", (char*)0, envInit);
    ERR_IF_NEG(ret, err_sys, "execle error");
}

ERR_IF_NEG(waitpid(pid, NULL, 0), err_sys, "wait error");

pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (0 == pid) {
    int ret = execlp("echoall", "echoall-arg0", "only 1 arg", (char*)0);
    ERR_IF_NEG(ret, err_sys, "execlp error");
}

END_TEST;


// ****************************************************************************
// hide std::system() function.
int system(const char *cmd) {
    pv("call custom system()\n");
    int     ret(0);
    pid_t   pid;

    if (!cmd) {
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        ret = -1;
    } else if (0 == pid) {
        // child process.
        execl("/bin/sh", "sh", "-c", cmd, (char*)0);
        _exit(127);
    }
    else {
        // parent
        while (waitpid(pid, &ret, 0) < 0) { // what value ret is set?
            if (errno != EINTR) {
                ret = -1;
                break;
            }
        }
    }
    return ret;
}

BEGIN_TEST(ProcessControll, System, @@);

using namespace std;

int st;
// st = ::system("date"); if you want use ISO C system function.
st = system("date");
ERR_IF_NEG(st, err_sys, "system(date) error");
printExit(st);

st = system("notttcmd");
ERR_IF_NEG(st, err_sys, "system(notttcmd) error");
printExit(st);

st = system("who; exit 44");
ERR_IF_NEG(st, err_sys, "system(who;exit 44)) error");
printExit(st);

END_TEST;


// ****************************************************************************
struct timeval      end;
unsigned long long  count(0);

void checkTime(const string &s) {
    struct timeval  t;
    gettimeofday(&t, NULL);

    static int lastD = 0;
    int d = end.tv_sec - t.tv_sec;
    if (d > 0 && d != lastD) {
        pv("%d\n", d);
        lastD = d;
    }

    if (t.tv_sec > end.tv_sec && t.tv_usec > end.tv_usec) {
        pv("%s count: %lld\n", s.c_str(), count);
        exit(0);
    }
}

// todo: test on uniprocesser cpu.
// ****************************************************************************
BEGIN_TEST(ProcessControll, Nice, @@);

pid_t   pid;
int     nzero;

int childIncr(100);         // according result on my mac, max nice is 39, NZERO == 20
int parentIncr(100);        // according result on my mac, max nice is 39, NZERO == 20

string procName; 

// 1. get nzero value.
#ifdef NZERO
nzero = NZERO;
#elif defined(_SC_NZERO)
nzero = sysconf(_SC_NZERO);
#else
#error no NZERO defined.
#endif

// set run time.
gettimeofday(&end, NULL);
end.tv_sec += 10;      

setbuf(stdout, NULL);   

// 2. fork child,
pid = fork();
ERR_IF_NEG(pid, err_sys, "fail to fork");
if (0 == pid) {
    // child
    procName = "child";
    pv("current nice: %d in child\n", nice(0) + nzero);
    errno = 0;
    ERR_IF((nice(childIncr) == -1 && errno != 0), err_sys, "fail to call nice for child");
    pv("adjust child nice by: %d, now nice: %d\n", childIncr, nice(0) + nzero);

    // compare with apue source codes.
    /*
    errno = 0;
    int ret = nice(childIncr);
    ERR_IF((ret == -1 && errno != 0), err_sys, "fail to call nice for child");
    pv("child nice adjust by: %d, now: %d\n", childIncr, ret + nzero);
     */

    // is nice(0) + nzero ( after call nice(childIncr) ) equals to nice(childIncr) + nzero ?? 
    // i think it's yes, because nice(int) always return the new nice value after inc operation. nice(0) inc 0 which directly return current nice value.
    // whereas nice(childIncr) return the original plus childIncr, so nice(0) [after calling nice(childIncr)] equals to nice(childIncr) directly.
    //
}
else {
    // parent
    procName = "parent";
    pv("current nice: %d in parent\n", nice(0) + nzero);
    errno = 0;      // clear errno in order to judge whether nice() call successfully.
    ERR_IF((nice(parentIncr) == -1 && errno != 0), err_sys, "fail to call nice for parent");
    pv("adjust parent nice by: %d, now nice: %d\n", parentIncr, nice(0) + nzero);
}

// 3. both run couting...
while (true) {
    if (++count == 0) {
        pv("%s counter overflow\n", procName.c_str());
    }
    checkTime(procName);
}

END_TEST;

// ****************************************************************************

BEGIN_TEST(ProcessControll, ProcessTime, @@);

auto printProcessTime = [] (clock_t wallTime, struct tms *begin, struct tms *end) {

    assert(begin && end);

    static long clockTick = 0;
    if (0 == clockTick) {
        clockTick = sysconf(_SC_CLK_TCK);
        ERR_IF_NEG(clockTick, err_sys, "sysconf(_SC_CLK_TCK) error");
    }

    pv("  real:   %7.2f\n", wallTime / (double)clockTick);
    pv("  user:   %7.2f\n", (end->tms_utime - begin->tms_utime) / (double)clockTick);
    pv("  sys:    %7.2f\n", (end->tms_stime - begin->tms_stime) / (double)clockTick);
    pv("  child user:   %7.2f\n", (end->tms_cutime - begin->tms_cutime) / (double)clockTick);
    pv("  child sys:    %7.2f\n", (end->tms_cstime - begin->tms_cstime) / (double)clockTick);
};

auto doCmd = [=](const std::string &cmd) {
    pv("command: %s\n", cmd.c_str());
    struct tms  processStart, processEnd;
    int         status;
    clock_t     start, end;

    start = times(&processStart);
    ERR_IF_NEG(start, err_sys, "fail to get process time");

    status = ::system(cmd.c_str());
    ERR_IF_NEG(status, err_sys, "fail to system(cmd)");

    end = times(&processEnd);
    ERR_IF_NEG(end, err_sys, "fail to get process time");

    printProcessTime(end - start, &processStart, &processEnd);
    printExit(status);
};

std::vector<string> cmds {"sleep 5", "date", "man bash > /dev/null"};
auto iter = cmds.begin();
while (iter != cmds.end()) {
    doCmd(*iter++);
}

END_TEST;


RUN_GTEST(ProcessControll, getSubDir, @@);


END_TEST;

NS_END(elloop);

