/*
 * =====================================================================================
 *
 *       Filename:  odr.cpp
 *
 *    Description:  odr(one define rule) test
 *
 *        Version:  1.0
 *        Created:  2015/01/03 14时51分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "odr.h"
#include "small_test_set.h"
#define	_GLIBCXX_DEBUG			/*  */
// #include "common/"
using namespace std;

int main ( int argc, char * argv[] ) {
    clock_t begin, end;
    begin = clock();
    printf ( "\nProgram %s\n\n", argv[0] );

    Odr odr;
    odr.init();
    cout << "main: " << odr.vec_.size() << endl;

    o2_optimize();


    
    end = clock();
    printf ( "time consumed: %lf\n", ( double ) ( end - begin ) / CLOCKS_PER_SEC );
    return EXIT_SUCCESS;
}   /* ----------  end of function main  ---------- */
