_Pragma("once")

#include <string>
#include <sstream>

namespace compare_version {

class Solution {
  public:
    int toInt(const std::string & str) {
      std::stringstream s(str);
      int i(0);
      s >> i;
      return i;
    }

    int compareVersion(std::string version1, std::string version2) {
      int part11 = toInt(version1.substr(version1.find_first_of('.')));
      int part21 = toInt(version1.substr(version2.find_first_of('.')));
      if (part11 > part21) {
        return 1;
      }
      else if (part11 < part21) {
        return -1;
      }
      else {
        int part21 = toInt(version1.substr(version1.find_first_of('.')));
        int part22 = toInt(version1.substr(version2.find_first_of('.')));
        if (part21 > part22) {
          return 1;
        }
        else if (part21 < part22) {
          return -1;
        }
        else {
          return 0;
        }
      }


      return 0;
    }
};

}
