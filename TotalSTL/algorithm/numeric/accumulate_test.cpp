#include "gtest/gtest.h"
#include "inc.h"
#include <numeric>
#include <string>
#include <vector>
#include <functional>
#include <map>
using namespace std;
using namespace std::placeholders;

NS_BEGIN(elloop);
NS_BEGIN(accumulate_test);



RUN_GTEST(NumericAlgorithm, SimpleUse, @);

vector<int> vi{1, 2, 3};
EXPECT_EQ(6, accumulate(vi.begin(), vi.end(), 0) );

END_TEST;




RUN_GTEST(NumericAlgorithm, NormalUse, @);

vector<int> vi{ 1, 2, 3 };
EXPECT_EQ(6, accumulate(vi.begin(), vi.end(), 0, plus<int>()));

END_TEST;






RUN_GTEST(NumericAlgorithm, ReturnValue, @);

vector<int> vi{ 1, 2, 3 };
int init(0);
accumulate(vi.begin(), vi.end(), init, plus<int>());
EXPECT_EQ(0, init);                 // test pass

END_TEST;






int func(int i, int j) 
{
    return i + j;
}

struct Functor
{
    int operator () (int i, int j)
    {
        return i + j;
    }
};

RUN_GTEST(NumericAlgorithm, MoreExamples, @);

vector<int> vi{ 1, 2, 3 };
EXPECT_EQ(6, accumulate(vi.begin(), vi.end(), 0, func));
EXPECT_EQ(6, accumulate(vi.begin(), vi.end(), 0, Functor()));
EXPECT_EQ(6, accumulate(vi.begin(), vi.end(), 0, [](int i, int j) ->int {return i + j;}));


int res = accumulate(vi.begin(), vi.end(), 
                        0, 
                        bind(plus<int>(), _1, 
                            bind(multiplies<int>(), _2, 2)
                        )
                    );

EXPECT_EQ(12, res);

// or use lambda.
res = accumulate(vi.begin(), vi.end(), 0, [](int i, int j) ->int { return i + 2*j; });
EXPECT_EQ(12, res);


struct Account
{
    int money;
};
vector<Account> va  = {Account{1}, Account{100}, Account{}};
int total = accumulate(va.begin(), va.end(), 
                        0, 
                        bind(plus<int>(), _1,
                            bind(&Account::money, _2)
                        )
                      );

EXPECT_EQ(101, total);

END_TEST;





RUN_GTEST(NumericAlgorithm, AdvancedUse, @);

map<string, int> m;
m.insert({ "dog",   3 });
m.insert({ "cat",   2 });
m.insert({ "fox",   1 });
m.insert({ "crow",  2 });

int animals(0);

animals = accumulate(m.begin(), m.end(),
                        0,
                        bind(plus<int>(), _1,
                            bind(&map<string, int>::value_type::second, _2)
                        )
                    );

EXPECT_EQ(8, animals);                  // animail totoal count is 8

END_TEST;





RUN_GTEST(NumericAlgorithm, TryToChangeInit, @);

// try1.
vector<int> vi{ 1, 2, 3 };
int init = 0;
//accumulate(vi.begin(), vi.end(), ref(init));  // compile error
EXPECT_NE(0, init);                 


// try2.
class Addable
{
public:
    Addable(int i=0) :i_(i) {}
    Addable operator + (const Addable& other) const
    {
        Addable a;
        a.i_ = i_ + other.i_;
        return a;
    }

    int     i_{ 0 };
};
Addable inita;
EXPECT_EQ(0, inita.i_);

vector<Addable> aa = {Addable(1), Addable(2), Addable(3)};
//accumulate(aa.begin(), aa.end(), ref(inita), plus<Addable>());  // also error.
EXPECT_NE(0, inita.i_);

END_TEST;


NS_END(accumulate_test);
NS_END(elloop);