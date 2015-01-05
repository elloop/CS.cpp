/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  algoritm test.
 *
 *        Version:  1.0
 *        Created:  2014/12/31 23时13分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <cstdio>
#include <ctime>
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

    so_print();

    end = clock();
    printf ( "time consumed: %lf\n", ( double ) ( end - begin ) / CLOCKS_PER_SEC );
    return EXIT_SUCCESS;
}   /* ----------  end of function main  ---------- */
