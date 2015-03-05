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

USING_NS_ELLOOP;
USING_NS_STD;

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
          half.insert(make_pair(target-numbers[i], i+1));
        }
      }

      return result;
    }

};

int main() {

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
  
  // rotate_array::Solution s;
  // int nums[] = {1, 2, 3, 4, 5};
  // int k = 6;
  // s.rotate(nums, sizeof nums/ sizeof nums[0], k);

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

  trailing_zeroes::Solution s;
  // psln(s.trailingZeroes(4));
  psln(s.trailingZeroes(2147483647));
  // for (int i=4; i<124; ) {
    // psln(i);
    // pln(s.trailingZeroes(i));
    // i += 5;
  // }

  // column_to_title::Solution s;
  // s.convertToTitle(52);

  return 0;
}



