/*
 * =====================================================================================
 *
 *       Filename:  print_util.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年03月21日 23时46分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  孙永健 (Ivan Sun), 912191009@qq.com
 *   Organization:  China
 *
 * =====================================================================================
 */

#ifndef  ALGORITHM_TEST_PRINT_UTIL_H
#define  ALGORITHM_TEST_PRINT_UTIL_H

#include <iostream>
#include <string>
namespace elloop_test {

#define psln(x) std::cout << #x " = " << (x) << std::endl
#define ps(x) std::cout << #x " = " << (x)
#define	cr std::cout << std::endl			/*  */

template <typename T>
inline void pc(const T & x) {
    std::cout << "************************" << x << "*********************";
}

template <typename T>
inline void pcln(const T & x) {
    std::cout << "************************" << x << "*********************" << std::endl;
}

template <typename T>
inline void p(const T & x) {
    std::cout << x;
}

template <typename T>
inline void pln(const T & x) {
    std::cout << x << std::endl;
}

/* template <typename T> */
/* inline void ps(const std::string & str, const T & x){ */
    /* std::cout << str << " = " << x; */
/* } */

/* template <typename T> */
/* inline void psln(const T & x){ */
    /* std::cout << _TEXT(x) << " = " << x << std::endl; */
/* } */

}

#endif   /* ----- #ifndef ALGORITHM_TEST_PRINT_UTIL_H----- */
