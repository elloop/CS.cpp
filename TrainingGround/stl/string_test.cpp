#include "string_test.h"
#include <string>

NS_BEGIN(elloop);
NS_BEGIN(string_test);

class Temp {
public:

};
std::string returnString() {
    return "s1";
}

TEST(StringTest, ConstructString) {
    pcln("StringTest ---> ConstructString");
    using std::string;
    string s1 = returnString();
    string s2 = "s2";
    string s3("s3");
    psln(s1);
    psln(s2);
    psln(s3);

}

NS_END(string_test);
NS_END(elloop);