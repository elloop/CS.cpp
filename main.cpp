/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  entrance
 *
 *        Version:  1.0
 *        Created:  2015/01/03 15时26分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

// #include "common/print_util.h"
#include "common/inc.h"
#include "common/print_util.h"
#include "stash/stash.h"

USING_NS_TEST;
USING_NS_STD;

int main() {

    int a(10);

    pcln(a);

    Stash my_stack;
    pln(my_stack.empty());

    pcln("ok");

    pcln("end");
    return 0;
}
