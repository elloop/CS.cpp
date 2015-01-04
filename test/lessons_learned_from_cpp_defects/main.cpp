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

#include "odr.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>

#define __g
int main ( int argc, char * argv[] ) {
    clock_t begin, end;
    begin = clock();
    printf ( "\nProgram %s\n\n", argv[0] );

    Odr odr;
    odr.init();
    
    end = clock();
    printf ( "time consumed: %lf\n", ( double ) ( end - begin ) / CLOCKS_PER_SEC );
    return EXIT_SUCCESS;
}   /* ----------  end of function main  ---------- */
