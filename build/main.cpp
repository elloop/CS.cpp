#include "inc.h"
#include "stash/stash.h"
#include "stack/stack.h"
#include <iostream>
#include <cstdio>

USING_NS_ELLOOP;
USING_NS_STD;

int main() {

    DEBUG_LOG("hello: %d", 10);

    Stash stash;
    psln(stash.empty());
    stash.push(new stack<int>());
    while (!stash.empty()) {
        pcln("poping stash into  st...");
        auto st = (stack<int>*)stash.pop();
        if (st != 0) {
            psln(st->empty());
            while (!st->empty()) {
                auto i = st->top();
                st->pop();
            }
        }
        else {
            pcln("st is null.");
        }

        delete st;
    }
    psln(stash.empty());
    return 0;
}
