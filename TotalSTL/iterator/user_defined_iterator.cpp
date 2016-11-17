#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <unordered_set>
#include <algorithm>
#include <array>
#include <iterator>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;



//----------------------- associative container inserter ----------------------
template <typename Con>
class asso_inserter_iterator 
    : public iterator<output_iterator_tag, typename Con::value_type>
{
public:
    explicit asso_inserter_iterator(Con &con) : conRef_(con) {}

    asso_inserter_iterator<Con>& operator= (const typename Con::value_type &val)
    {
        conRef_.insert(val);
        return *this;
    }

    asso_inserter_iterator<Con>& operator * () 
    {
        return *this;
    }

    asso_inserter_iterator<Con>& operator ++ ()
    {
        return *this;
    }

    asso_inserter_iterator<Con>& operator ++ (int)
    {
        return *this;
    }

protected:
    Con     &conRef_;
};

// convenience function to create asso_inserter_iterator.
template <typename Con>
inline asso_inserter_iterator<Con> asso_inserter(Con &con)
{
    return asso_inserter_iterator<Con>(con);
}


BEGIN_TEST(UserDefinedIterator, AssoInserter, @);

set<int> uset;

asso_inserter_iterator<set<int>>  ainserter(uset);

*ainserter = 10;
++ainserter;
*ainserter = 20;
++ainserter;
*ainserter = 30;

printContainer(uset, "uset: ");     // 10 20 30

asso_inserter(uset) = 1;
asso_inserter(uset) = 2;
printContainer(uset, "uset: ");     // 1 2 10 20 30

// compile error on vs 2015
//array<int, 5> a = {11, 22, 33, 44, 55};
//copy(a.begin(), a.end(), asso_inserter(uset)); // 1 2 10 11 20 22 30 33 44 55
//printContainer(uset, "uset: ");

END_TEST;




NS_END(elloop);
