#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(enum_class);


enum class Week
{
    Sun = 0,
    Mon = 1,
    Tue = 2,
    Wen = 3,
    Thu = 4,
    Fri = 5,
    Sat = 6,
};




RUN_GTEST(EnumClassTest, ConvertToInt, @);

Week today = Week::Fri;

int int_today = static_cast<int>(today);

psln(int_today);


END_TEST;



enum Color
{
    kRed,
    kGreen,
    kBlue,
    kYellow,
    kPink,
    kPurple,
    kColorCount,
};

RUN_GTEST(EnumClassTest, Unscoped, @);

Color colors[kColorCount];

for (int i=0; i<kColorCount; ++i) 
{
    colors[i] = static_cast<Color>(i);
}

for (int i=0; i<kColorCount; ++i) 
{
    Color color_i = static_cast<Color>(kRed + i);
    assert(colors[i] == color_i);
}


END_TEST;


RUN_GTEST(EnumClassTest, Arithmetic, @);

Color red = kRed;
psln(typeid(red).name());   // 

long i = 1;
bool same = std::is_same<decltype(i), decltype(i + red)>::value;
EXPECT_TRUE(same);

END_TEST;


NS_END(enum_class);
NS_END(elloop);