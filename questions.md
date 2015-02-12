# cpp questions & summary.
===

#Questions.
---
##  2015/2/11
1. things in container must have copy constructor, try it.
2. 《对不起，青春》
3. see understanding_cpp11/compatibility.h: using BaseTest::BaseTest(10); compile error.

## 2015/2/9
1. how to return a null-refrence in function stack/stack.h:top() ?


#Summary.
---
## grammer.
1. don't include headers in your custom namespace.
```
namespace elloop {
#include <iostream>

}
```
compile this, and see what will happend.

2. Linux和其它代码库里的宏都用do/while(0)来包围执行逻辑，因为它能确保宏的行为总是相同的，而不管在调用代码中使用了多少分号和大括号。
```
#define f(x) foo(x); bar(x)

// 1. in if.
void g() {
    if (b) 
        f(x);
}
// g() == 
if (b)
    foo(x);
bar(x);
//not you want. maybe you can add {} to macro define. but :

// 2. in if else
#define f(x) { foo(x); bar(x); }
void q() {
    if (b) 
        f(x);
    else
        xx();
}
// equal to
void q() {
    if (b) {
        foo(x);
        bar(x);
    };
    else
       xx();
}
// wrong, ';' before else.
```
## GDB
|command|description|
|-------|-----------|
|r|run|
|c|continue|
|step (s) | step into|
|next () | setp over|
|q| quit|
|b linenumber/file:function/functon...| breakpoints|
|info b| list of breakpoints|
|l | list source codes|
|p name | print macro value/ variable value ... |
| macro expand macroname | expand macro (need g++ compiler options: -gdwarf-2 -g3 ) |

