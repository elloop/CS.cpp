#include "raw_string_literal.h"

NS_BEGIN( elloop )
NS_BEGIN( raw_string_literal )

TEST( RawStringLiteral, Test ) {
    using std::cout;
    using string = std::string;
    cout << R"(hello\nworld)";
    string s = R"(hello\nworld)";
    EXPECT_EQ( "hello\\nworld", s );

    //cout << u8R"(ÄãºÃ)";
    //cout << uR"(hello)";


}

NS_END( raw_string_literal )
NS_END( elloop )