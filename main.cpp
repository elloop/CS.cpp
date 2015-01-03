/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  entrance
 *
 *        Version:  1.0
 *        Created:  2015/01/03 15时26分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (http://blog.csdn.net/elloop/), jacysun@gmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */

// #include "common/print_util.h"
#include "common/inc.h"
#include "common/print_util.h"

using namespace std;
USING_NS_TEST;
USING_NS_STD;

ostream& operator << (ostream & os, const Test & t) {
    os << t.num_;
    return os;
}

int main() {

    Test tt;
    pcln(tt);

    pln(tt);
    p(tt);
    return 0;
}
