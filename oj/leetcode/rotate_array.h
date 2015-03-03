_Pragma("once")

#include <vector>
#include <cstring>
#include "inc.h"
namespace rotate_array {

class Solution {
  public:
  void rotate(int nums[], int n, int k) {
    k %= n;
    if (0 == k) {
      return;
    }

    int * temp = new int[k];
    int i(0);
    int * src(temp);
    while (i < k) {
      *src++ = *(nums + n - k + i++);
    }

    // ::memcpy(nums+n-k, nums, k);
    ::memmove(nums+k, nums, sizeof(int) * (n-k));
    ::memcpy(nums, temp, sizeof(int) * k);

    // for (auto i : nums) {
      // psln(i);
    // }

    delete [] temp;
  }
};

}
