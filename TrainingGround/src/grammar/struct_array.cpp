#include "gtest/gtest.h"
#include "struct_array.h"

NS_BEGIN(elloop);

BEGIN_TEST(StructArrayTest, SingleStructInit, @)
pcln("StructArrayTest -------------> SingleStructInit");

auto printSimple = [](const Simple& s)
{
    LOGD("simple: (%d, %d)\n", s.x, s.y);
};

// 定义结构体对象的两种方式，推荐第二种，显式指定字段名。
Simple s1 = { 1, 2 };
printSimple(s1);

Simple s2 = { s2.x = 1, s2.y = 2 };
printSimple(s2);

auto printCombo = [](const Combo& c)
{
    LOGD("combo: (%d, %d; %d)\n", c.sim.x, c.sim.y, c.z);
};

// 含有结构体成员的结构体的初始化

Combo   c1 = { {1, 2}, 3 };
printCombo(c1);

Combo   c2 = { { 1, 2 }, c2.z = 3 };
printCombo(c2);
END_TEST


BEGIN_TEST(StructArrayTest, StructArrayInit, @)
pcln("StructArrayTest -------------> StructArrayInit");

auto printSimple = [](const Simple& s)
{
    LOGD("simple: (%d, %d)\n", s.x, s.y);
};

auto printCombo = [](const Combo& c)
{
    LOGD("combo: (%d, %d; %d)\n", c.sim.x, c.sim.y, c.z);
};

// 在结构体只有默认的构造函数时，在初始化结构体数组时，
// 每个数组元素的初始化需要值的个数等于该结构体的成员变量个数
// 从Simple的定义可以看到，它由两个int组成，因此需要两个值来初始化一个数组元素
Simple  s1[] = {
    1, 2,
    3, 4,
};
size_t  len = ARRAY_LEN(s1);
EXPECT_EQ(2, len);
for (size_t i = 0; i < len; ++i)
{
    printSimple(s1[i]);
}
// or use {}. s1 is the same with s2.
Simple  s2[] = {
    { 1, 2 },
    { 3, 4 }
};
len = ARRAY_LEN(s2);
EXPECT_EQ(2, len);

Simple  s3[] = {
    1, 2, 3
};
len = ARRAY_LEN(s3);
EXPECT_EQ(2, len);
EXPECT_TRUE(3 == s3[1].x);
EXPECT_TRUE(0 == s3[1].y);

pcln("combo struct");

// 复合型的结构体也是一个道理，如果没有自定义构造函数，那么在初始化结构体数组时
// 每个数组元素需要的值的个数等于该结构体每个成员初始化所需的个数之和，
// simple需要两个， Combo的第三个参数需要一个，所有初始化一个Combo数组元素需要
// 三个值。
Combo   c1[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};
len = ARRAY_LEN(c1);
EXPECT_EQ(3, len);
// 或者，
Combo   c2[] = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
};
len = ARRAY_LEN(c2);
EXPECT_EQ(3, len);
// 或者，
Combo   c3[] = {
    { { 1, 2 }, 3 },
    { { 4, 5 }, 6 },
    { { 7, 8 }, 9 },
};
len = ARRAY_LEN(c2);
EXPECT_EQ(3, len);
for (size_t i = 0; i < len; ++i)
{
    printCombo(c3[i]);
}

// 注意：在阅读初始化结构体数组的代码时，可以按一下顺序来拆分代码：
// 以c3数组的初始化为例：
//  Combo   c3[] = {
//      { { 1, 2 }, 3 },
//      { { 4, 5 }, 6 },
//      { { 7, 8 }, 9 },
//  };
// 首先从等号右边看起，右边最外层就是一对大括号，这是最基本的要求。
// 剥离这最外层的大括号之后，看里面的以逗号分隔的单元是什么东西，分两种情况：
// 1) 每个单元是一对大括号(c3的初始化就是)；
//      那么大括号括起来的单元的个数，就是这个数组元素的个数；
//      每个单元再展开，去掉两端的大括号，用里面的单元去初始化一个结构体元素，
//      这里面的元素可能还是以逗号分隔的单元，根据结构体的结构来进行对应的匹配
//      即可。每个子单元也可能会出现值个数不足的情况，此时缺少的值将被填充为默认值
// 2) 每个单元直接是值；
//      取决于每个结构体需要的值的个数n，数组元素个数=ceil(单元数/n), 最后的结
//      构体如果得不到足够的值来初始化，结果将初始化为0;

// 如下面的例子，c4 将含有3个元素（因为等号右边的花括号里面，最外层有三个子单元）
// 第一个元素Combo ： { { }， 3} 来初始化， simple将被初始化为（0，0），z将被初始化为
// 3
// 第二个元素Combo: { {4, }, 6 } 来初始化， simple（4,0), z = 6
// 第三个元素Combo: { {7, 8}, 9} 来初始化， simple(7, 8), z = 9
Combo   c4[] = {
    { {}, 3 },
    { { 4, }, 6 },
    { { 7, 8 }, 9 },
};
len = ARRAY_LEN(c4);
EXPECT_EQ(3, len);
EXPECT_TRUE(0 == c4[0].sim.x);
EXPECT_TRUE(0 == c4[0].sim.y);
EXPECT_TRUE(3 == c4[0].z);

EXPECT_TRUE(4 == c4[1].sim.x);
EXPECT_TRUE(0 == c4[1].sim.y);
EXPECT_TRUE(6 == c4[1].z);

END_TEST;




NS_END(elloop);




NS_BEGIN(from_opengl_test);

#define LEN(x) sizeof x / sizeof x[0]

template <typename T>
struct vec2
{
    typedef T       value_type;

    value_type      x;
    value_type      y;

    template <typename U>
    vec2(const U & u) : x(u), y(u)
    {}

    template <typename U, typename V>
    vec2(const U& u, const V& v) :
        x(u), y(v)
    {}
};

template <typename T>
struct color
{
    typedef T       value_type;

    value_type      r;
    value_type      g;
    value_type      b;

    /*color(value_type r1, value_type g1, value_type b1) :
        r(r1), g(g1), b(b1)
        {
        }*/
};


struct RawColor
{
    int     r;
    int     g;
    int     b;
};

struct Compo
{
    vec2<float> pos;
    color<int>  color;
};




BEGIN_TEST(StructArrayTest, FromOpenGLTest, @)
typedef vec2<float> float2;

vec2<float> f = { 10 };

vec2<float> ary[2] = { { 10, 11 }, { 1, 0 } };
//vec2<float> ary2[] = { 10, 11 };

float2 fs1[] = {
    1, 2,
    3, 4,
    5, 6,
    7, 8
};
size_t len1 = LEN(fs1);
for (size_t i = 0; i < len1; ++i)
{
    float2 temp = fs1[i];
}

float2 fs2[] = {
    { 1, 2 },
    { 3, 4 },
    { 5, 6 },
    { 7, 8 }
};
len1 = LEN(fs2);
for (size_t i = 0; i < len1; ++i)
{
    float2 t = fs2[i];
}

typedef color<int> colori;
colori cs1[] = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 9 }
};
len1 = LEN(cs1);
for (size_t i = 0; i < len1; ++i)
{
    colori temp = cs1[i];
}

colori cs2[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};
len1 = LEN(cs2);
for (size_t i = 0; i < len1; ++i)
{
    colori t = cs2[i];
}


RawColor rcs1[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};

len1 = LEN(rcs1);
for (size_t i = 0; i < len1; ++i)
{
    RawColor t = rcs1[i];
}


Compo compos[] = {
    { 1, 2 }, { 1, 1, 1 },
    { 11, 22 }, { 11, 12, 13 }
};

END_TEST



NS_END(from_opengl_test);
