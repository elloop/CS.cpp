#include "user_define_literal.h"
#include "gtest/gtest.h"

NS_ELLOOP_BEGIN

#ifdef _MSC_VER
#else
Person operator "" _person(const char * data, unsigned int len) {
	// just a demo, no real meaning.
	Person p;
	p.setName(data);
	p.setAge(len);
    return p;
}
#endif


TEST(UserDefineLiteral, Construct) {
    Person p("lionel", 10);
    EXPECT_EQ(10, p.age());
    EXPECT_EQ(0, strcmp("lionel", p.name()));
    p.setName("hello");
    EXPECT_EQ(0, strcmp("hello", p.name()));
    p.setName("");
    EXPECT_EQ(0, strcmp("", p.name()));
    p.setName("ok");
    p.setName(nullptr);
    EXPECT_EQ(0, strcmp("ok", p.name()));
    p.setName(p.name());
    EXPECT_EQ(0, strcmp("ok", p.name()));
    
    Person p2("fine", 10);
    p.setName(p2.name());
    EXPECT_EQ(0, strcmp("fine", p.name()));
    EXPECT_EQ(0, strcmp(p.name(), p2.name()));

}

void takePersion(Person p)
{

}
TEST(UserDefineLiteral, UsingLiteralConstruct) {
#ifdef _MSC_VER
#else
	takePersion("Tom"_person);
#endif
}



NS_ELLOOP_END