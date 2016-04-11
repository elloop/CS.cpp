#include "user_define_literal.h"
#include "gtest/gtest.h"

NS_ELLOOP_BEGIN

#ifdef _MSC_VER
#else
/*
Person operator "" _person(const char * data, unsigned int len) {
	// just a demo, no real meaning.
    // Person p;
	Person p(data, len);
	p.setName(data);
	p.setAge(len);
    return p;
}
*/
#endif


BEGIN_TEST(UserDefineLiteral, Construct, @);
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

END_TEST;

void takePersion(Person p)
{

}
BEGIN_TEST(UserDefineLiteral, UsingLiteralConstruct, @);
#ifdef _MSC_VER
#else
	// takePersion("Tom"_person);
#endif
END_TEST;



NS_ELLOOP_END
