#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include <vector>
#include <cstring>
#include <valarray>
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(rotate_array)

class Solution {
  public:
  void rotate(int nums[], int n, int k) {
    // --------------------------------------------------
    // method 1.
    // --------------------------------------------------
    // k %= n;
    // if (0 == k) {
      // return;
    // }

    // int * temp = new int[k];
    // int i(0);
    // int * src(temp);
    // while (i < k) {
      // *src++ = *(nums + n - k + i++);
    // }

    // // ::memcpy(nums+n-k, nums, k);
    // ::memmove(nums+k, nums, sizeof(int) * (n-k));
    // ::memcpy(nums, temp, sizeof(int) * k);

    // // for (auto i : nums) {
      // // psln(i);
    // // }

    // delete [] temp;

    // --------------------------------------------------
    // method 2 : using valarray
    // --------------------------------------------------
    std::valarray<int> val_array(nums, n);
    val_array = val_array.cshift(-k);
    for (auto i=0; i<n; ++i) {
      nums[i] = val_array[i];
    }
  }
};

NS_END(rotate_array)
NS_END(elloop)