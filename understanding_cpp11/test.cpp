#include "compatibility.h"

USING_NS_ELLOOP;

#define TEST(x) do { delete (new (x))->run(); } while (0);
int main() {

    TEST(Compatibility);
    return 0;
}
