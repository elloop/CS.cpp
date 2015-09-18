#include "rvalue_refrence_and_move_constructor.h"
#include "smart_pointer.h"

NS_BEGIN(elloop)
NS_BEGIN(rvalue_refrence_and_move_constructor)



TEST( RValueReference, CopyConstructorWithPointer ) {

	pcln( "old TEST" );

	u_ptr<int> pi(new int(10));
	HasPointer<int> a(pi.get());
    HasPointer<int> b( a );
    EXPECT_EQ( 10, a.data() );
    EXPECT_EQ( a.data(), b.data() );


    pcln( "just for fun" );
    HasPointer<HasPointer<HasPointer<HasPointer<HasPointer<int>>>>> hh;
    EXPECT_EQ( 0, hh.data().data().data().data().data() );

	pcln("another test");
	u_ptr<Dog> jim(new Dog("jim"));
    HasPointer<Dog> hj( jim.get() );
	EXPECT_EQ("jim", hj.data().name_);

    // 能不能用一个同一个对象初始化同一个对象？ 比如，同一个Dog
    // 也就是说，在copy constructor中是否要判断是自我构造
    // Dog * dog;
    // new (dog)Dog();
    //Dog * dd;
    //new (*dd)(dd);
    //new (&dd)Dog();
    //psln( dd->name_ );

	
}

// record how many times each constructor(destructor) are called.
int BigDog::ctr = 0;
int BigDog::cptr = 0;
int BigDog::mtr = 0;
int BigDog::dtr = 0;

BigDog getTempBigDog() {
	// dog is a xvalue. (expiring value, 将亡值)
	BigDog dog;
	LOGD("temp dog in %s, ptr is %d\n", __FUNCTION__, (int*)dog.knowledge_);
	return dog;
}

TEST(RValueReference, MoveConstructorTest) {
	// bad practice of using move semantics.
	BigDog bd;
	LOGD("bd ptr is %d\n", (int*)bd.knowledge_);
	BigDog bd1(std::move(bd));
	// bd is moved and invalid. although it doesn't called copy constructor and is efficient.
	EXPECT_EQ(nullptr, bd.knowledge_);
	LOGD("bd1 ptr is %d\n", (int*)bd1.knowledge_);

	// i didn't find how to turn off RVO in vs. so in vs:
	// this will call:
	// constructor : 1
	// move constructor : 1 
	// destructor : 2
	BigDog dog1 = getTempBigDog();
	LOGD("temp dog in %s, ptr is %d\n", __FUNCTION__, (int*)dog1.knowledge_);

	EXPECT_TRUE(std::is_rvalue_reference<decltype(std::move(getTempBigDog()))>::value);
	EXPECT_FALSE(std::is_rvalue_reference<decltype(getTempBigDog())>::value);

	// capture a temp no-name object using rvalue_reference.
	BigDog&& rvalueDog = getTempBigDog();
	EXPECT_TRUE(std::is_rvalue_reference<decltype(rvalueDog)>::value);


}

Movable getTempMovable()
{
	Movable temp = Movable();
	LOGD("moveable in getTempMovable is %d\n", temp.hm_.data_);
	return temp;
}
TEST(RValueReference, UsingStdMove) {
	Movable m(getTempMovable());
	LOGD("movable in testbody is %d\n", m.hm_.data_);
}

TEST(RValueReference, ReferenceFolding) {
	typedef int& T1;
	EXPECT_TRUE(std::is_lvalue_reference<T1>::value);
	EXPECT_TRUE(std::is_lvalue_reference<T1&>::value);
	EXPECT_TRUE(std::is_lvalue_reference<T1&&>::value);

	typedef int&& T2;
	EXPECT_TRUE(std::is_rvalue_reference<T2>::value);
	EXPECT_TRUE(std::is_lvalue_reference<T2&>::value);
	EXPECT_TRUE(std::is_rvalue_reference<T2&&>::value);

}

void targetFunction(int && m) { LOGD("rvalue reference target\n"); }
void targetFunction(int & m) { LOGD("lvalue reference target\n"); }
void targetFunction(const int && m) { LOGD("const rvalue reference target\n"); }
void targetFunction(const int & m) { LOGD("const lvalue reference target\n"); }
/*
template <typename T>
void forwarding(T&& t) {
	targetFunction(std::forward<T>(t));
}
*/

TEST(RValueReference, PerfectForward) {
	int a;
	int b;
	const int c = 1;
	const int d = 0;

	forwarding(a);
	forwarding(std::move(b));
	forwarding(c);
	forwarding(std::move(d));

}

NS_END( rvalue_refrence_and_move_constructor )
NS_END( elloop )