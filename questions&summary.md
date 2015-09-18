# cpp questions & summary.
===

#Questions.
---
## 2015/2/19
1. what is move assignment operaor, how to define it?

##  2015/2/11
1. things in container must have copy constructor, try it.
2. 《对不起，青春》
3. see understanding_cpp11/compatibility.h: using BaseTest::BaseTest(10); compile error.

## 2015/2/9
1. how to return a null-refrence in function stack/stack.h:top() ?


#Summary.
---

##leetcode oj.
1. use hash_table to cache heavy-visiting, from O(n) to O(1).
2. if your codes pass almost all test cases, then check the data type you use(maybe because of overflow.) to pass the remain cases.


### easy

### medium

### hard

---
## grammer.

### thread
4. 默认情况下，c++11中的原子类型的变量在线程中总是保持着顺序执行的特性。称此为“顺序一致性”，即代码在线程中运行的顺序与程序员看到的代码一致。 -- 《深入理解c++11新特性》
Hardware Look:
1). strong ordered: 机器指令按正常的顺序（代码的顺序）执行. example: x86, sparc(tso).
2). weak ordered: 机器指令可以被打乱，指令流水线。example: Alpha, PowerPC, Itanlium, ArmV7, use memory barrier to be strong ordered.
in cpp11: Layer between Machine Codes and HighLevel languages is implemented by compiler. compiler may rearrange the instructions to achieve high performance.
in cpp11 atomic operation always request sequential consisitent, means:
1) it forbidens x86(strong ordered model) to rearrange and optimize instructions.
2) it forbidens PowerPC not only to rearrange and optimize instructions, but also insert memory barrier.
in order to avoid bad performance, cpp11 use the concept of "memory order" to free the restrictions.

|enum vallue| meaning |
|------------|--------|
|memory_order_relaxed| no sequential guarrantee|
|memory_order_acquire | 本线程中，所有后续的读操作必须在本条原子操作完成后执行|
|memory_order_release | 本线程中，所有之前的写操作完成后才能执行本条原子操作|
|memory_order_acq_rel | 同时包含memory_order_acquire and memory_order_release|
|memory_order_consume | 本线程中，所有后续的有关本原子类型的操作，必须在本条原子操作完成后执行|
|memory_order_seq_cst | sequential consisitent 全部存取都按顺序执行|

3. operator = is implicitly declared as deleted because stack<int> declares a move constructor or move assignment operator. tested in gcc 4.8.2.

2. don't include headers in your custom namespace.
```
namespace elloop {
#include <iostream>

}
```
compile this, and see what will happend.

1. Linux和其它代码库里的宏都用do/while(0)来包围执行逻辑，因为它能确保宏的行为总是相同的，而不管在调用代码中使用了多少分号和大括号。
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

