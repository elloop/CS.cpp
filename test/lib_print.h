/*
 * =====================================================================================
 *
 *       Filename:  lib_print.h
 *
 *    Description:  so_print()
 *
 *        Version:  1.0
 *        Created:  2015/01/03 12时33分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */


#ifndef  LIB_PRINT_H
#define	LIB_PRINT_H			/*  */

void so_print();

template <typename T>
class A {
    protected:
        int num;
};

template<typename T>
class B : public A<T> {
    public:
        void init() {
            this->num = 0;
        }
};

struct t {
    int w,h;
};

#endif     /* -----  not LIB_PRINT_H  ----- */
