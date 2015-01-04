/*
 * =====================================================================================
 *
 *       Filename:  lib_print.cpp
 *
 *    Description:  so_print()
 *
 *        Version:  1.0
 *        Created:  2015/01/03 12时34分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

#include "lib_print.h"
#include <cstdio>
void so_print() {
    t tt = {10, 20};
    t tt2 = {tt2.w = 20, tt2.h = 10};
    printf("tt: w = %d, h = %d\n", tt2.w, tt2.h);
}

