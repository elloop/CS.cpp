#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "inc.h"
#include "valid_parentheses.h"
#include "rotate_array.h"
#include "title_to_number.h"
#include "trailing_zeroes.h"
#include "column_to_title.h"
#include "compare_version.h"
#include "intersection_of_linklist.h"
#include "zig_zag.h"
#include "min_stack.h"
#include "gtest/gtest.h"

NS_BEGIN(elloop);

using std::vector;
using std::map;

class S {
  public:
    static vector<int> solve(vector<int>& numbers, int target) {
      vector<int> result;
      vector<int>::size_type i(0);
      map<int, int> half;
      for (i; i<numbers.size(); ++i) {
        if (half.find(numbers[i]) != half.end()) {
          result.push_back(half.find(numbers[i])->second);
          result.push_back(i+1);
          return result;
        }
        else {
          half.insert(std::make_pair(target-numbers[i], i+1));
        }
      }

      return result;
    }

};

BEGIN_TEST(TwoSum, Test1, @@);
  /*
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> src;
  src.assign(a, a+sizeof a / sizeof a[0]);
  int target = a[2] + a[3];
  vector<int> result = S::solve(src, target);

  for (auto i : result) {
    pln(i);
  }
  */

  // TODO: more solutions.
  // valid_parentheses::Solution s;
  // string str("()[]}");
  // psln(s.isValid(str));
  
  rotate_array::Solution s;
  int nums[] = {1, 2, 3, 4, 5};
  int k = 6;
  s.rotate(nums, sizeof nums/ sizeof nums[0], k);

  // TODO: make a summary about memcpy and memmove.
  // test memcpy and memmove.
  // int a[] = {1, 2, 3, 4};
  // int b[] = {0, 0, 0,0,0};
  // int n(4);
  // // ::memcpy(b+1, (int*)a, sizeof (int) * (n));
  // ::memmove(a+1, a, sizeof (int) *(n-1));
  // ::memcpy(a+1, a, sizeof (int) *(n-1));
  // print_array(a);

  // title_to_number::Solution s;
  // psln(s.titleToNumber("ZA"));

  // trailing_zeroes::Solution s;
  // psln(s.trailingZeroes(4));
  // psln(s.trailingZeroes(2147483647));
  
  // for (int i=4; i<250; ) {
    // p(i); p(": ");
    // pln(s.trailingZeroes(i));
    // i += 5;
  // }

  // compare_version::Solution s;
  // psln(s.compareVersion("1", "2.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.10000.1.1.1.1.1.2.3.4.5.6.7"));
  // psln(s.compareVersion("1.1.0", "1.1"));

  // string s1("01");
  // string s2("1");
  // vector<int> x = s.getNumbers(s1);
  // vector<int> x2 = s.getNumbers(s2);
  // int i = x.size();
  // int j = x2.size();
  // psln(i);
  // psln(j);

  // psln(s.compareVersion(s1, s2));

  // string v1, v2;
  // while (cin >> v1 >> v2) {
    // psln(s.compareVersion(v1, v2));
  // }
  // column_to_title::Solution s;
  // s.convertToTitle(52);

  // using namespace intersection_of_linklist;
  // intersection_of_linklist::Solution s;

  // Solution::ListNode * p = new Solution::ListNode[13];
  // Solution::ListNode * q = new Solution::ListNode[13];
  // psln(s.getIntersectionNode(p, q));
  // delete p;
  // delete q;

  // zig_zag::Solution s;
  // psln(s.convert("PAYPALISHIRING", 3));

  // char str[] = "hello";
  // string s(str, str + 5);
  // psln(s);

/*   using min_stack::MinStack; */
  // MinStack s;
  // s.push(10);
  // s.push(11);
  // s.push(1);
  // psln(s.top());
  // s.pop();
  // psln(s.top());
  /* psln(s.getMin()); */

  // using min_stack::MinStack2;
  // MinStack2 s;

  // s.push(2147483646);
  // s.push(2147483646);
  // s.push(2147483647);

  // psln(s.top());

  // s.pop();

  // psln(s.getMin());
  // s.pop();
  // psln(s.getMin());
  // s.pop();
  // s.push(2147483647);
  // psln(s.top());
  // psln(s.getMin());
  // s.push(-2147483648);
  // psln(s.top());
  // psln(s.getMin());
  // s.pop();
  // psln(s.getMin());

END_TEST;


NS_END(elloop);