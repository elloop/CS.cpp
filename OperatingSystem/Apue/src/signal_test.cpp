#include "include/inc.h"
#include "include/apue.h"
#include <iostream>
#include <signal.h>
#include <pwd.h>

NS_BEGIN(elloop);

// ****************************************************************************
void sigUser(int sig) {
    if (SIGUSR1 == sig) {
        pv("SIGUSR1 received\n");
    }
    else if (SIGUSR2 == sig) {
        pv("SIGUSR2 received\n");
    }
    else {
        err_dump("unkown sig: %d\n", sig);
    }
}

// use `man signal` to see detail desc about SIGUSR1 etc.

// note: wrapped in gtest, the behaviour of this case is not the same with apue.
// to see the same, move this code outside gtest.
BEGIN_TEST(SignalTest, SigUser, @@);

ERR_IF(signal(SIGUSR1, sigUser) == SIG_ERR, err_sys, "fail to signal SIGUSR1");
ERR_IF(signal(SIGUSR2, sigUser) == SIG_ERR, err_sys, "fail to signal SIGUSR2");
while (true) {
    pause();        // explain @10.10
}

END_TEST;

// ****************************************************************************

// todo: debug this case use gdb, rewrite this in a single program if necessary.
// i don't know why this case stopped after printing several times "in alarmSig handler".

void alarmSig(int sig) {
    struct passwd *rootpwd;
    pv("in alarmSig handler\n");
    rootpwd = getpwnam("root");
    ERR_IF(rootpwd == NULL, err_sys, "fail to getpwnam for root");
    alarm(1);
}

BEGIN_TEST(SignalTest, ReentrantFunc, @@);

ERR_IF(signal(SIGALRM, alarmSig) == SIG_ERR, err_sys, "fail to signal SIGALRM");
alarm(1);

struct passwd   *usrpwd;
while (true) {
    usrpwd = getpwnam("elloop");
    ERR_IF(usrpwd == NULL, err_sys, "fail to getpwnam for elloop");
    if (strcmp(usrpwd->pw_name, "elloop") != 0) {
        pv("name corrupted, pw_name is: %s\n", usrpwd->pw_name);
    }
}

END_TEST;

NS_END(elloop);
