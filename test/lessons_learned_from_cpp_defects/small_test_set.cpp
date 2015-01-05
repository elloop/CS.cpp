/*
 * =====================================================================================
 *
 *       Filename:  small_test_set.cpp
 *
 *    Description:  lots of small test.
 *
 *        Version:  1.0
 *        Created:  2015/01/05 07时36分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

#include "small_test_set.h"
// compile with command:
// g++ small_test_set.cpp -g -O2 -fno-strict-aliasing
void o2_optimize() {
    int64_t mem(0);
    int32_t * ptr_low = (int32_t*)&mem;
    int32_t * ptr_high = ptr_low + 1;

    *ptr_high = 0xffffeeee;
    *ptr_low = 0xaaaabbbb;
    printf("mem=%lx, high=%x, low=%x\n", mem, *ptr_high, *ptr_low);
}
