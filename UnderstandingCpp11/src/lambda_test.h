#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include "inc.h"
NS_BEGIN(elloop)
NS_BEGIN(lambda_test)

/*
lambda formula:
[capture](param) [mutable] ->return_type { body; }

1. capture can be following:
    =: capture all variables by value in scope.
    &: capture all variables by reference in father scope.
    this: capture this by value.
    &this: capture this by reference.
    empty: capture nothing.
    examples: 
    [=, &a, &b]: 引用方式传递a,b, 其他所有变量按值传递。
    [&, a, b]: 按值方式传递a,b, 其他所有变量按引用传递。
    [=, a]: 错误，不能存在重复的声明。=已经包含了按值方式传递a。
2. param
    like normal function params, can be empty meaning no params.
3. [mutable]
    values in the capture list is const in default.
    if you want to change values in captures list, you should specified the [mutable].
    if mutable specified, the capture values can be modified in <body>.
    if you use mutable, you can't omit param list even if it's empty.
4. -> return_type
    can omit if the <body> doesn't return a value.
    can omit if compiler can deduce its return type.
5. body
    normal function body.

the simplest lambda function can be : []{};

lambda的局限性： 仅能捕获父作用域的自动变量。
lambda注意事项：
1. 拷贝成本。当使用by_value的方式捕获变量的时候，会产生copy开销。
2. by_reference传递的时候，虽然没有copy开销，
   但是此时lambda与父作用域共享变量，需小心处理两者关系，
   尤其是当存在多处修改该变量的代码的时候。
*/

// util function use by unit test.
class DoubleFunctor {
public:
    int operator() (int x) {
        return 2 * x;
    }
};

NS_END(lambda_test)
NS_END(elloop)
