
#include "test.h"
#include <stdio.h>
void test_read_char_to_c() {
    
    char c;

    while ( (c = getchar()) != EOF ) {
        printf("%d\n", c);
        putchar(c);
        putchar(10);
    }
}
