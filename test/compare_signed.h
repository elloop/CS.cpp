/*
 * =====================================================================================
 *
 *       Filename:  compare_signed.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/12/31 11:47:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jacy sun (https://github.com/elloop), elloop@foxmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */


#ifndef  TEST_DATA_H
#define TEST_DATA_H

struct data {
    // int flag:1; is wrong for t.flag = 1.
    unsigned int flag:1;
    int other:31;
};
void test_compare();

#endif     /* -----  not TEST_DATA_H  ----- */
