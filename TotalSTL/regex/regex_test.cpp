#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>
#include <regex>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;




//-----------------------  Advance  ----------------------
BEGIN_TEST(RegexTest, Unicode, @);

std::string s("this subject has a submarine as a subsequence");
//std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
std::regex e("\\s*[^\u4e00-\u9fa5]+\\s*");

std::regex_iterator<std::string::iterator> rit(s.begin(), s.end(), e);
std::regex_iterator<std::string::iterator> rend;

while (rit != rend)
{
    std::cout << rit->str() << std::endl;
    ++rit;
}

//char32_t utf32[] = U"hello = \u4F60\u597D\u554A";


END_TEST;



NS_END(elloop);