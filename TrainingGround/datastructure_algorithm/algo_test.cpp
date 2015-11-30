#include "algo_test.h"
#include "gtest/gtest.h"
#include <vector>

NS_BEGIN(elloop);
using namespace std;

void permutation(vector<char>& ary, int begin, int end, vector<vector<char>> & result) {
  if (begin >= end)
  {
    result.push_back(ary);
  }
  else {
    for (int i = begin; i < end; i++) {
      swap(ary[i], ary[begin]);
      permutation(ary, begin + 1, end, result);
      swap(ary[i], ary[begin]);
    }
  }
}

BEGIN_TEST(AlgoTest, Permutation, @)
  pcln("AlgoTest --> Permutation");
  vector<vector<char>> result;
  vector<char> ary{ 'a', 'b', 'c', 'd' };
  permutation(ary, 0, ary.size(), result);
  for (auto ary: result)
  {
    for (auto item:ary)
    {
      p(item);
    }
    cr;
  }
END_TEST

NS_END(elloop);