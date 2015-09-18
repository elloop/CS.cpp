#include "variadic_template.h"
#include "smart_pointer.h"
#include <stdarg.h> // for va_start, va_end, va_arg

NS_BEGIN( elloop )
NS_BEGIN( variadic_template )

// va_arg samples. in old c++ codes.
int sum( int count, ... ) {
    int result( 0 );
    va_list params;
    va_start( params, count );
    for ( int i = 0; i < count; ++i ) {
        result += va_arg( params, int );
    }
    va_end( params );
    return result;
}

TEST( VariadicTemplate, OldVa_arg ) {
    EXPECT_EQ( 5, sum( 2, 1, 4 ) );
    EXPECT_EQ( 10, sum( 3, 1, 4, 5 ) );
    EXPECT_EQ( 75, sum( 15, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5) );
}

TEST( VariadicTemplate, TupleTest ) {

    Tuple<int> t1;
    t1.first;

    Tuple<double, int> t2;
    //psln( (double)t2.first );

    Tuple<int, float, double, int> t;
    //t.head;
}

TEST( VariadicTemplate, FactorialTest ) {
    long f = Multiply<1>::value;
    EXPECT_EQ( 1, f );

    f = Multiply<1, 2>::value;
    EXPECT_EQ( 2, f );

    f = Multiply<10, 10>::value;
    EXPECT_EQ( 100, f );

    f = Multiply<1, 2, 10, 10, 10, 10, 10, 10, 10>::value;
    EXPECT_EQ( 20000000, f );
}

TEST( VariadicTemplate, PrintfTest ) {
    Printf( "hello, world in Printf\n" );
    Printf( "hello, world in Printf£¬ following a str: %s\n",
            std::string( "here" ) );

}

TEST(VariadicTemplate, VariadicPrintf) {
	using Dog = smart_pointer::Dog;
	Dog dog("Henry");
	vPrint("hello\n", std::string("world\n"), 'h', '\n', 10, '\n', 11.111, 
		'\n', dog, '\n');
}

TEST(VariadicTemplate, VariadicCountTest) {

	auto c = VariadicCount<int>::value;
	EXPECT_EQ(1, c);

	c = VariadicCount<int, double, float>::value;
	EXPECT_EQ(3, c);

	c = VariadicCount<int, double, float, std::string, 
		smart_pointer::Dog>::value;
	EXPECT_EQ(5, c);

	c = numOfVariadic(1, 2.0, 3.0, "hello", smart_pointer::Dog("Alves"));
	EXPECT_EQ(5, c);

}

TEST(VariadicTemplate, TemplateVariadicTemplate) {
	Container<int, A>;
	Container<int, A, B>;
	//Container<A, B>;	//error: A is a template class. need type for 1st param.

}

TEST(VariadicTemplate, PerfectForwardUsingVariadicTemplate) {
	Fa fa;
	Fb fb;
	auto mul = build<MultiTypes>(fa, fb);
    //Fa fa1 = mul.t_;
    EXPECT_EQ( &mul.t_, &fa );
    // how to find fb in mul?

}

NS_END( variadic_template )
NS_END( elloop )
