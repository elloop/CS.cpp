#include "inc.h"
#include <string>

NS_BEGIN(elloop);
NS_BEGIN(string_algorithm);

using namespace std;

// reverse range of str: [begin, end]
void reverse_string(string& s, size_t begin, size_t end)
{
    while (begin < end)
    {
        char c = s[begin];
        s[begin++] = s[end];
        s[end--] = c;
    }
}

void rotate_string(string& s, size_t m)
{
    reverse_string(s, 0, m);
    reverse_string(s, m+1, s.size() -1);
    reverse_string(s, 0, s.size() - 1);
}



BEGIN_TEST(StringAlgorithm, ReverseWord, @@);

string str("abcdefg");
psln(str);
rotate_string(str, 1);
psln(str);

END_TEST;


NS_END(string_algorithm);
NS_END(elloop);