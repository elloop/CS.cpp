
#include "compare_signed.h"
#include <stdio.h>

void test_compare() {

    struct data t;
    t.flag = 1;

    if ( t.flag == 1 ) {
        printf("flag == 1");
    }
    else {
        printf("flag == %d\n", t.flag);
        printf("flag != 1");
    }
}
