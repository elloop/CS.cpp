#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "inc.h"
#include "gtest/gtest.h"

NS_BEGIN(elloop);

using std::vector;

class NumArray {
public:
    // _sums[i] = sum of a[0 ... i]
    NumArray(vector<int> nums) {
        int n = nums.size();
        if (n > 0) {
            _sums.reserve(n);
            _sums[0] = nums[0];
            for (int i=1; i<n; ++i) {
                _sums[i] = _sums[i-1] + nums[i];
            }
        }
    }

    int sumRange(int i, int j) {
        if (i == 0) { return _sums[j]; }
        return _sums[j] - _sums[i-1];
    }

private:
    vector<int> _sums;
};


BEGIN_TEST(RangeSum, Test1, @@);

NumArray na({-2, 0, 3, -5, 2, -1});
psln(na.sumRange(0, 2));
psln(na.sumRange(2, 5));
psln(na.sumRange(0, 5));

END_TEST;


NS_END(elloop);
