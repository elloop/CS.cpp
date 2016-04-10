#include "string_test.h"
#include "util/FileReader.h"
#include <string>

NS_BEGIN(elloop);
NS_BEGIN(string_test);

class Temp {
public:

};
std::string returnString() {
    return "s1";
}

BEGIN_TEST(StringTest, ConstructString, @)
    using std::string;

    string s1 = returnString();
    string s2 = "s2";
    string s3("s3");
    psln(s1);
    psln(s2);
    psln(s3);

    pcln("construct with char array.");

    unsigned long fileSize(0);
    unsigned char * res = FileReader::getInstance()->getFileData("test.txt", "rb", &fileSize);
    res[fileSize - 1] = 0;
    psln(res);

    string s4((char*)res, fileSize);
    psln(s4);

    char ary[] = { 0x41, 0x42, 0x61, 0x62}; // ABab
    string s5(ary, ARRAY_LEN(ary));
    psln(s5);

    EL_SAFE_DELETE_ARRAY(res);


END_TEST;


NS_END(string_test);
NS_END(elloop);