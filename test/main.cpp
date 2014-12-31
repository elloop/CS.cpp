/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  test lessons learned from cpp defects
 *
 *        Version:  1.0
 *        Created:  2014/12/31 11:35:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jacy sun (https://github.com/elloop), elloop@foxmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

#include "compare_signed.h"
#include "test.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <cmath>
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

    //test_read_char_to_c();
    // test_compare();
    float f1 = 0.333333;
    float f2 = 1.0 / 3;


    printf("f1 = %lf\n", f1);
    printf("f2 = %lf\n", f2);

    float f_abs = fabs(f1 - f2);
    
    printf("f_abs = %lf\n", f_abs);
    if ( f_abs < 0.00001 ) {
        printf("same float");
    }
    else {
        printf("not same float");
    }
    putchar(10);

    int * ptr = 0;
    delete ptr;

    end = clock();
    printf ( "time consumed: %lf\n", ( double ) ( end - begin ) / CLOCKS_PER_SEC );
    return EXIT_SUCCESS;
}   /* ----------  end of function main  ---------- */
