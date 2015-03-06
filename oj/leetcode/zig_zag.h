_Pragma("once")

#include <string>

namespace zig_zag {

  // P   A   H   N
  // A P L S I I G
  // Y   I   R
  //
  // convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
  
class Solution {
  public:
    std::string convert(std::string s, int nRows) {
      std::string result("");
      size_t len = s.size();
      int j(0);
      int next_j(0);
      for (int i=0; i<nRows; ++i) {
        j = i;
        while (j < len) {
          result.append(s[j]);
          next_j = j + 2 * (nRows - 1) + 2 * i;

          if (next_j != j && next_j < len) {
            result.append(s[next_j]);
          }

        }
      }
      return result;
    }

};

}
