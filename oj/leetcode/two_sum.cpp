#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "inc.h"
#include "valid_parentheses.h"

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
  
  rotate_array::Solution s;



  return 0;
}
