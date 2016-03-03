---
layout: post
title: "【C++ STL学习与应用总结】22: 函数组合之1：如何使用std::bind (since C++11)"
category: c++
tags: [stl]
description: ""
---

**本系列文章的目录在这里：[目录](http://blog.csdn.net/elloop/article/details/50357205). 通过目录里可以对STL总体有个大概了解**

##前言

std::bind是STL实现函数组合概念的重要手段，本文总结了std::bind这个模板函数的用法，给出了std::bind绑定普通函数(函数指针)、lambda表达式、成员函数、成员变量、模板函数、嵌套std::bind等的语法细节及注意的问题。

文中涉及到的术语：

- [std::placeholders](http://www.cplusplus.com/reference/functional/placeholders/) : 占位符，被占位符绑定的参数，在实际调用中被实际参数代替。

- [std::decay](http://www.cplusplus.com/reference/type_traits/decay/) : 退化类型

- [std::forward](http://www.cplusplus.com/reference/utility/forward/?kw=forward) : 转发

- [Callable](http://en.cppreference.com/w/cpp/concept/Callable) : 可调用对象

- [lambda](http://en.cppreference.com/w/cpp/language/lambda) : functors的语法糖，定义一个函数(对象), 当做函数来使用

- [trailing return types](http://en.cppreference.com/w/cpp/language/function) : 用于在声明（定义）函数时，函数返回值依赖于其参数的类型；或者是函数返回类型描述比较复杂时，用来简化类型书写

- [reference_wrapper<T>](http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper) : 引用包装类模板，用于把一个应用封装成一个对象，以便于在容器里，或者传递引用。

<!--more-->

## std::bind 是什么

看命名空间前缀std就知道，bind是标准库的亲儿子，包含在`<functional>`中.

std::bind 是一个函数模板, 它就像一个函数适配器，可以把一个原本接收N个参数的函数fn，通过绑定一些参数，返回一个接收M个参数的函数ret，同时还可以实现参数顺序调整等操作。

它的原型有两种形式，如下：

### 原型

```c++
// simple(1)	
template <class Fn, class... Args>
  /* unspecified */ bind (Fn&& fn, Args&&... args);

 // with return type (2)	
template <class Ret, class Fn, class... Args>
  /* unspecified */ bind (Fn&& fn, Args&&... args);
```

bind返回一个基于fn的函数对象(function object), 其参数被绑定到args上.

**<font color="red">fn的参数要么是绑定到值，要么是绑定到placeholders(占位符，如_1, _2, ..., _N)</font>**

### 参数:

- fn： 一个[Callable](http://en.cppreference.com/w/cpp/concept/Callable)对象(可以是function objects， 函数指针或引用，成员函数指针或成员变量指针), 它的参数将被args绑定

- args: 可变长参数，或者是具体的值，或者是[占位符(placeholder)](http://www.cplusplus.com/reference/functional/placeholders/). <font color="red">注意：其长度必须与fn接收的参数个数一致</font>

### 返回值

令bind的返回值为ret:

```c++
auto ret = std::bind(fn, args&&...)
// or
auto ret = std::bind<Ret>(fn, args&&...)
```

其返回值ret是一个未指定类型T的function object，T满足如下条件：`std::is_bind_expression<T>::value == true`. 

ret这个类型，包含如下的成员：

**1.成员变量**:

- 1: `decay<Fn>::type`类型的对象(暂且叫_Myfun), 由`std::forward<Fn>(fn)`构造得来。简单来说，就是保存了bind时候传过来的fn对象.

- 2: `tuple<typename decay<Types>::type>` 类型的对象(暂且叫它_Mybargs), 这个tuple的每个元素的类型是`decay<Args_i>::type`, 是由调用bind时，第二个参数args...转发而来, 即`forward<Args_i>(arg_i)`, Args_i 表示args中的第i个. 通俗来说，这个对象保存了bind时传过来的所有的参数args...。

ret的这个两个成员对象分别保存了bind传来的函数和参数以实现将来的调用任务。
    
**2. 构造函数**:

- 如果ret的所有成员对象都是可以拷贝构造的，那么它自身也是可拷贝构造的
    
- 同理，如果所有成员都是可移动构造的，那么它自身也是可移动构造的

**3. 成员类型：result_type**

- 如果Fn是一个函数指针或者成员函数指针，那么ret的result_type就是Fn的返回值类型.

- 如果Fn是一个类，并且它内部定义了一个result_type, 那么result_type就等于Fn::result_type.

- 如果ret是使用第二种形式调用bind得到的，即`auto ret = bind<Ret>(fn , args)`, 那么result_type就是Ret.

**4. 成员函数 operator()**  （<font color="red">此为重点，毕竟bind的返回值ret，就是用来当做函数调用的</font>）

ret作为bind的返回值，假设我们这样调用ret: ret(a1, a2, a3, ... ai); 此时ret内部保存的那个`decay<Fn>::type`类型的对象：_MyFun, 将被调用, 它将会按照如下的方式来为a1, a2, ..., ai 来绑定值：

- 如果调用bind时指定的是`reference_wrapper<T>`类型的，比如在调用bind时使用了std::ref 或者 std::cref来包装args，那么调用ret内部的_MyFun时，对应参数会以T&类型传入_MyFun.

- 如果在创建ret时候，使用了嵌套的bind，即ret = bind(fn, args...)的参数列表args中，存在某个arg：使得`std::is_bind_expression<decltype(arg)>::value == true`, 那么这个嵌套的bind表达式会被立即调用，其返回值会被传给ret里的_MyFun作为参数(也就是说嵌套的bind返回值会被当做ret调用时的参数)， 如果嵌套的bind里用到了占位符placeholder, 这些placeholder将会从ret的调用参数ret(a1, a2, ... ai)中对应位置选择.
        
- 如果在创建ret时候，使用了占位符placeholders, 即 ret = bind(fn, arg1, arg2, ..., _1, _2, ...), (对于_1, _2..., 有`std::is_placeholder<T>::value != 0`). 那么a1, a2, ..., ai会以转发的形式`forward<ai>(ai)`传递给_MyFun, a1对应_1, a2对应_2, 以此类推.

- 否则，ret内部保存的args，即上文提到的_Mybargs(bind调用时绑定的参数们)将被以左值的形式传给_MyFun以完成调用，这些参数和g有相同cv限定属性.

如果g(a1, a2, ..., ai)中，有哪些ai没有匹配任何的placeholders，比如在调用bind时，placeholder只有_1, 而g(a1, a2, a3), 那么a2, a3就是没有匹配的，没有被匹配的参数将被求值，但是会被丢弃。

如果g被指定为volatile(volatile or const volatile)，结果是未定义的.

"说了那么多，你就是想装b"， 还是看看bind在实际代码中的应用吧

## 从两个极端情况出发，正确理解bind过程和std::placeholders的使用

为了更容易理解并使用bind，再强调一下这句话：**<font color="red">fn的参数要么是绑定到值，要么是绑定到placeholders</font>**

### 极端1：完全绑定到值

```c++
void f(int n1, int n2, int n3)
{
    cout << n1 << " " << n2 << " " << n3 << endl;
}

// f的三个参数，全部绑定到值，对empty_args的调用将不需要提供参数
auto empty_args = bind(f, 1, 2, 3);     
empty_args();               // 1 2 3
```

### 极端2：完全绑定到std::placeholders

```c++
void f(int n1, int n2, int n3)
{
    cout << n1 << " " << n2 << " " << n3 << endl;
}

int ret4() 
{ 
    cout << "ret4() called" << endl;
    return 4; 
}

// f参数都使用占位符绑定, 需要提供至少三个参数
auto need_3args = bind(f, _1, _2, _3);
need_3args(1, 2, 3);            // 1 2 3
need_3args(1, 2, 3, 4, 5);      // 1 2 3; 4和5被丢弃
need_3args(1, 2, 3, ret4());    // ret4() called<cr> 1 2 3; 会调用ret4(), 但是返回的4被丢弃
```

除了这两种极端的情况，大部分情形下，bind是混合着值和占位符来进行绑定的。

### bind过程分析及调用传参控制

在分析bind的绑定过程时，<font color="red">如何确定bind调用有没有错误，以及调用bind返回值ret的时候如何正确传参？</font>比如，对下面的bind调用：

```c++
void f(int n1, int n2, int n3, int n4, int n5)
{
    cout << n1 << " " << n2 << " " << n3 << " " << n4 << " " << n5 << endl;
}

// 如何分析bind的调用是否正确
auto mix1 = bind(f, 1, 2, 3, _1, _2);
auto mix2 = bind(f, 1, 2, 3, 4, _1, _2);
auto mix3 = bind(f, 1, 2, 3, _2, _1);
auto mix4 = bind(f, _3, 2, 3, 4, _1);
auto mix5 = bind(f, _1, _1, _1, _1, _1);
auto mix6 = bind(f, _100, _50, _10, _5, _1);


// 如何填写mix的调用参数，他需要几个参数？
// mix1(...); 
// mix3(...); 
// mix4(...); 
// mix5(...); 
```

**<font color="red">分析过程：</font>**

**1. bind(f, args...)的合法性分析**

设f需要的参数个数为N， bind(f...)中，提供的值的个数为V， 提供的占位符个数为S. 

对于合法的bind调用，必有 N == V + S. 如果V + S 超出N或者小于N, 编译都会报错。

所以上面的mix定义中，只有mix1, mix3, mix4, mix5是合法的。mix2中参数个数已经有6个，而f只需要5个。mix6的参数个数对，但是占位符太大了, 在VC++(2013)编译器实现中最大为20。

**2. bind返回值ret的调用传参写法**

设bind(f, args...)中最大的占位符为_M. ( 如mix1, mix2, mix3中 M=2； mix4中 M=3; mix5中 M=1; mix6中M=100; )

则：

- 参数个数

    ret的调用中至少要提供 M 个参数，因为_1~_M正是从ret(args...)参数列表中从左到右来按下标顺序绑定参数的，少于M个会报错，多于M个则被丢弃.

- 参数顺序

    ret(args...)中参数与placeholders: _1~_M的对应是很简单的，下标从1开始，依次对应。但是绑定到f的顺序是由bind(fn, args...)中placeholders的顺序决定的.如bind(f, _1, _2, _3, _4, _5)就是从左到右的顺序把ret(args...)里的参数绑定到f；而bind(f, _5, _4, _3, _2, _1)则是按相反的顺序绑定。

于是，对于上文中定义的合法mix的调用示例及输出可以是：

```c++
auto mix1 = bind(f, 1, 2, 3, _1, _2);
auto mix3 = bind(f, 1, 2, 3, _2, _1);
auto mix4 = bind(f, _3, 2, 3, 4, _1);
auto mix5 = bind(f, _1, _1, _1, _1, _1);

mix1(4, 5);                 // 1 2 3 4 5; M = 2;
//mix1(4);                  // no, 参数太少了
mix3(5, 4);                 // 1 2 3 4 5; M = 2; 
mix4(5, 0, 1);              // 1 2 3 4 5; M = 3; 第一个参数5给_1, 第三个参数1给_3, 第二个参数0被丢弃，因为bind中没用到_2.
mix5(5);                    // 5 5 5 5 5; M = 1;
```

你可能注意到mix6中的_100, _50, 这样大的占位符是编译不过的。

placeholders的最大值，在VC++上是20， 它的最大值依赖于具体的编译器实现，不需要纠结这个最大值. 一般不会使用很大的占位符，因为一旦你使用了一个占位符_100，虽然只用了一个，但是这就意味着调用者需要提供至少100个参数，你是想弄死谁？

下面就按照fn的分类给出bind的调用示例：

## std::bind 绑定普通函数、lambda表达式

```c++
#include <functional>

// 定义两个函数，乘、除法
double multiply(double d1, double d2)
{
    return d1 * d2;
}

double divide(double d1, int n)
{
    assert(n != 0);
    return d1 / n;
}

//----------------------------- begin of new test -----------------------------
RUN_GTEST(FunctorTest, Bind, @);        // google gtest 的简单封装，可以当做一个普通函数的开始！

using std::bind;                        // for std::bind
using namespace std::placeholders;      // for _1, _2, _3 ...

// 做“无用功”， same函数跟multiply一样，接收两个参数，并且顺序也是一致
auto same = bind(multiply, _1, _2);
EXPECT_EQ(200.0, same(2, 100));         

// 第一个参数使用占位符，第二个单数绑定为2.0, 从而返回一个函数仅需要传入一个参数，
// 返回其2倍。
auto doublize = bind(multiply, _1, 2.0);
EXPECT_EQ(200.0, doublize(100));

// 全部使用参数绑定，ret_20不需要参数即可调用，返回20
auto ret_20 = bind(multiply, 2, 10);
EXPECT_EQ(20.0, ret_20());

// 正常的相除函数, arg1/arg2
double d1 = divide(10, 2);
EXPECT_EQ(5, d1);

// 通过bind，交换两个参数的顺序，revertDivide(arg1, arg2)将返回arg2/arg1
auto revertDivide = bind(divide, _2, _1);
double d2 = revertDivide(10, 2);
EXPECT_EQ(1 / 5.0, d2);

// bind的第二种形式，显式指定返回值类型为int
auto rounding = bind<int>(divide, _1, _2);
auto i1 = rounding(10, 3);
bool isSameType = is_same<int, decltype(i1)>::value;    // i1 是int
EXPECT_TRUE(isSameType);
EXPECT_EQ(3, i1);

// bind lambda函数
auto lambda_func = [](int x) -> int { return x; };
auto ret_100 = bind(lambda_func, 100);
EXPECT_EQ(100, ret_100);

// 使用bind适配一个函数 
std::function<void(int)> func_with_1args;
func_with_1args = bind(multiply, 10, _1);

END_TEST;
```

## std::bind 绑定类成员函数、成员变量

成员函数区别于普通函数的一个特殊之处在于，其第一个参数必须是该类型的一个对象(或对象的指针或引用)

```c++
class Foo
{
public:

    void f(int n1, int n2, int n3)
    {
        cout << n1 << " " << n2 << " " << n3 << endl;
    }

    int a_ { 100 };
};

//----------------------------- begin of new test -----------------------------
RUN_GTEST(FunctorTest, Bind, @);

Foo foo;
Foo& foo_ref= foo;

// 成员函数原型：Foo::f(int n1, int n2, int n3);
// 使用Foo::f, 需要四个参数，1.Foo类型的对象(或其指针或引用); 2~4个参数则赋值给n1, n2, n3

// 对返回值mfarg4的调用将需要4个参数: 按顺序绑定到占位符_1, _2, _3, _4.
auto mfarg4 = bind(&Foo::f, _1, _2, _3, _4);
// 使用对象本身调用
mfarg4(foo, 10, 20, 30);        // 10 20 30; 
// 使用对象指针调用
mfarg4(&foo, 10, 20, 30);       // 10 20 30; 
// 使用对象引用
mfarg4(foo_ref, 10, 20, 30);    // 10 20 30; 

// 对返回值mfarg3的调用将需要三个参数：分别绑定到三个占位符，f的第四个参数将使用固定左值30.
auto mfarg3 = bind(&Foo::f, _1, _2, _3, 30);
mfarg3(foo, 10, 20);            // 10 20 30; 

// 对返回值mfarg2的调用将需要两个参数：分别绑定到两个占位符，f的后两个参数将使用固定左值20, 30.
auto mfarg2 = bind(&Foo::f, _1, _2, 20, 30);
mfarg2(foo, 10);                // 10 20 30; 

// 对返回值mfarg1的调用将仅需要一个参数foo对象，绑定到唯一的占位符，后单个参数将使用bind中的固定左值10,20,30.
auto mfarg1 = bind(&Foo::f, _1, 10, 20, 30);
mfarg1(foo);                    // 10 20 30;

// 完全使用左值绑定，返回值mfarg0将不需要使用参数进行调用.
auto mfarg0 = bind(&Foo::f, foo, 10, 20, 30);
mfarg0();                       // 10 20 30

// 使用对象指针或引用也可以
auto mfarg01 = bind(&Foo::f, &foo, 10, 20, 30);
mfarg01();                      // 10 20 30
auto mfarg02 = bind(&Foo::f, foo_ref, 10, 20, 30);
mfarg02();                      // 10 20 30

// 把一个成员函数赋值给一个std::function
std::function<void(int, int, int)> normal_func;
normal_func = bind(&Foo::f, foo, _1, _2, _3);
normal_func(10, 20, 30);        // 10 20 30

//------------------------------ 绑定成员变量a_ ---------------------------

// bind成员变量，其第一个参数必须是该类型的一个对象(或对象或引用), 指针不行！！

auto bind_mv = bind(&Foo::a_, _1);
cout << bind_mv(foo);           // 100
cout << bind_mv(foo_ref);       // 100
//cout << bind_mv(&foo);        // error, 成员变量不能用对象指针来绑定

END_TEST;
```

## std::bind 绑定模板函数

```c++

// 定义一个函数模板，返回两数之和，返回值是两数之和的类型。使用了c++11中的trailing return types特性.
template <typename T1, typename T2>
auto add(const T1 & t1, const T2& t2) -> decltype(t1 + t2)
{
    return t1 + t2;
}

// work with template function.
auto addby2 = bind(add<double, double>, _1, 2.0);
cout << addby2(10.2);                             // 12.2
```

## 嵌套std::bind共享std::placeholder.

```c++

void print(int n1, int n2, int n3)
{
    cout << n1 << " " << n2 << " " << n3 << endl;
}

// 定义一个辅助函数
auto addby1 = [] (int x) -> int 
{ 
    cout << "addby1() called" << endl;
    return (x+1); 
};

// 嵌套的bind在使用外层bind()中的placeholders
auto nested_f = bind(print, _1, bind(addby1, _1), _2); 

nested_f(1, 3);                 // addby1() called<cr> 1 2 3
```

## `reference_wrapper<T>`类型, 实现绑定引用

```c++
int x(10);

// 第二个参数使用引用x，第三个参数使用值x
auto bind_ref = bind(print, 1, std::cref(x), x);  
bind_ref();                // 1 10 10; 

x = 100;

bind_ref();                // 1 100 10; 第二个参数跟着x变化了，第三个则没变
```

## bind与标准库协同工作

```c++
RUN_GTEST(FunctorTest, BindPredefinedFunctors, @);

// all predefined functors:
// negate, plus, minus, multiplies, divides, modulus, equal_to, 
// not_equal_to, less, greater, less_equal, greater_equal,
// logical_not, logical_and, logical_or, bit_and, bit_or, bit_xor

auto tenTimes = bind(multiplies<int>(), _1, 10);
EXPECT_EQ(100, tenTimes(10));
EXPECT_EQ(200, tenTimes(20));
EXPECT_EQ(300, tenTimes(30));

vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
// nested bind. output v[i] if 10*v[i] > 50.
copy_if(v.begin(), v.end(),
    ostream_iterator<int>(cout, ", "),
    bind(greater<int>(),
        bind(multiplies<int>(), _1, 10),
        50));                               // 6,7,8,
cr;

END_TEST;
```

## bind与智能指针

```c++
RUN_GTEST(FunctorTest, BindSmartPointer, @);

struct Temp 
{
    Temp(int i=0) : i_(i) {}
    void print() { pln(i_); }
    int i_;
};

vector<shared_ptr<Temp>> vs =
{
    shared_ptr<Temp>(new Temp(1)),
    shared_ptr<Temp>(new Temp(2)),
    shared_ptr<Temp>(new Temp(3)),
};

for_each(vs.begin(), vs.end(), bind(&Temp::print, _1));  // 1<cr>2<cr>3<cr>

bind(&Temp::print, vs[0])();        // 1
bind(&Temp::print, vs[1])();        // 2
bind(&Temp::print, vs[2])();        // 3

END_TEST;
```

## last but not least

bind中的参数是被copy或者是被move到目标函数的，除非显示指定按引用传递, 用`std::ref` 或者`std::cref`来包裹参数，否则是不会按引用来传递的。<font color="red">这意味着你要意识到, 在bind一个大的对象作为参数的时候可能存在的拷贝开销, 应该尽量用引用**</font>

同时，因为move会改变对象的状态，因此，所以当你在bind参数列表里<font color="red">重用placeholders的时候，要考虑到参数已经被moved掉的情况</font>, 标准建议：只有在参数是左值或者不可移动的右值的时候，重用placeholders才有意义。

## <font color="red">源码</font>

- [标准c++参考的测试代码1](http://www.cplusplus.com/reference/functional/bind/?kw=bind)

- [标准c++参考的测试代码2](http://en.cppreference.com/w/cpp/utility/functional/bind)

- [本文的测试代码](https://github.com/elloop/CS.cpp/blob/master/TotalSTL/functor/bind_test.cpp)

---------------------------

**作者水平有限，对相关知识的理解和总结难免有错误，还望给予指正，非常感谢！**

**欢迎访问[github博客](http://elloop.github.io)，与本站同步更新**


