#include "smart_pointer.h"

NS_BEGIN( elloop )
NS_BEGIN( smart_pointer )

// NOTICE!!
// in following codes:
// u_ptr<T> =  std::unique_ptr<T>
// s_ptr<T> = std::shared_ptr<T>
// w_ptr<T> = std::weak_ptr<T>

TEST( SmartPointer, UniquePointer ) {

    u_ptr<int> p { new int( 10 ) };
    EXPECT_EQ( 10, *p );

    u_ptr<int> q( new int( 10 ) );
    EXPECT_EQ( 10, *q );
    
    u_ptr<Dog> pd1( new Dog("Tom") );

    //u_ptr<Dog> pd2 = pd1;             // error: copy assignment is deleted.
    u_ptr<Dog> pd2 = std::move(pd1);    // use move assignment.
    EXPECT_EQ( nullptr, pd1 );
    EXPECT_NE( nullptr, pd2 );
    pd2.reset();
    EXPECT_EQ( nullptr, pd2 );
    //*pd1 = Dog( "tom2" );               // error: pd1 is empty(reseted).

	// try to use unique_ptr in stl container.
	/*std::vector<u_ptr<Dog>> ptr_vec;
	ptr_vec.push_back(pd1);				// fail, copy constructor is deleted.
	ptr_vec.push_back(pd2);*/


}
TEST(SmartPointer, SharedPointer) {
	// shared_ptr 放到容器里，引用计数加1，那么容器销毁他会自动减1吗？
	s_ptr<Dog> pd1(new Dog("Jerry"));
	EXPECT_EQ(1, pd1.use_count());
	EXPECT_STREQ("Jerry", pd1->name().c_str());

	s_ptr<Dog> pd2 = pd1;
	EXPECT_EQ("Jerry", pd2->name());

	EXPECT_EQ(2, pd1.use_count());
	EXPECT_EQ(2, pd2.use_count());

	pd1.reset();
	//EXPECT_EQ(1, pd1.use_count());		// fail: pd1 use_count is 0 now.
	EXPECT_EQ(0, pd1.use_count());
	EXPECT_EQ(1, pd2.use_count());

	//auto t = pd1->name();					// error: SEH exception throwed.
	EXPECT_EQ(nullptr, pd1);

	auto t = pd2->name();
	EXPECT_EQ("Jerry", t);

	pd2.reset();

	EXPECT_EQ(0, pd1.use_count());
	EXPECT_EQ(0, pd2.use_count());
	EXPECT_EQ(nullptr, pd1);
	EXPECT_EQ(nullptr, pd2);

	// TODO: how to TEST this ?
	// A shared_ptr that does not own any pointer is called an empty shared_ptr.
	// A shared_ptr that points to no object is called a null shared_ptr and 
	// shall not be dereferenced.Notice though that an empty shared_ptr is not 
	// necessarily a null shared_ptr, and a null shared_ptr is not necessarily 
	// an empty shared_ptr.
	s_ptr<Dog> pd3;
	//EXPECT_NE(nullptr, pd3);			// fail, they are equal.

}

TEST(SmartPointer, WeakPointer) {
	s_ptr<Dog> sp1(new Dog("David"));
	w_ptr<Dog> wp1 = sp1;
	EXPECT_EQ(1, sp1.use_count());
	EXPECT_EQ(1, wp1.use_count());		// weak_ptr doesn't own the pointer.

	EXPECT_TRUE(checkValidity(wp1));	// valid.
	sp1.reset();
	EXPECT_FALSE(checkValidity(wp1));	// invalid, due to sp1's reset().
	EXPECT_EQ(0, wp1.use_count());		
	//EXPECT_EQ(nullptr, wp1);			// compile error: wp1 has no ==.


	s_ptr<Dog> sp2(new Dog("Bob"));
	wp1 = sp2;
	EXPECT_TRUE(checkValidity(wp1));	// valid again.
	sp2 = sp1;
	EXPECT_FALSE(checkValidity(wp1));	// invalid, due to sp2's assignment=.
	EXPECT_EQ(0, wp1.use_count());
	//EXPECT_EQ(nullptr, wp1);

}

std::ostream& operator<<(std::ostream & os, const Dog & dog) {
	os << dog.name();
	return os;
}

NS_END( smart_pointer )
NS_END( elloop )