/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015/01/03 20时48分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char * argv[] ) {
    clock_t begin, end;
    begin = clock();
    printf ( "\nProgram %s\n\n", argv[0] );

    std::cout << 1000 << std::endl;

    end = clock();
    printf ( "time consumed: %lf\n", ( double ) ( end - begin ) / CLOCKS_PER_SEC );
    return EXIT_SUCCESS;
}   /* ----------  end of function main  ---------- */
