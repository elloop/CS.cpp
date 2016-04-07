#include "inc.h"
#include <string>

NS_BEGIN(elloop);
NS_BEGIN(string_algorithm);

using namespace std;

// recursive perm.
void perm_string(string& s, size_t begin, size_t end)
{
    if (begin == end) 
    {
        psln(s);
    }
    else
    {
        for (size_t i=begin; i<=end; ++i) 
        {
            swap(s[i], s[begin]);
            perm_string(s, begin + 1, end);
            swap(s[i], s[begin]);
        }
    }
}


// perm with dictionary order.


BEGIN_TEST(StringAlgorithm, PermRecursive, @@);

string str("abcd");
perm_string(str, 0, str.size() -1 );

END_TEST;




NS_END(string_algorithm);
NS_END(elloop);