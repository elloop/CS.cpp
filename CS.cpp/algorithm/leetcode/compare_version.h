#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include <string>
#include <sstream>
#include <vector>
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(compare_version)

class Solution {
public:
	int toInt(const std::string & str) {
		std::stringstream s(str);
		int i(0);
		s >> i;
		return i;
	}

	std::vector<int> getNumbers(const std::string & version) {
		std::vector<int> result;
		size_t last_pos(0), pos(0);
		pos = version.find_first_of('.', last_pos);
		while (pos != std::string::npos) {
			result.push_back(toInt(version.substr(last_pos, pos - last_pos)));
			last_pos = pos + 1;
			pos = version.find_first_of('.', last_pos);
		}
		result.push_back(toInt(version.substr(last_pos)));

		return result;
	}

	int compareVersion(std::string version1, std::string version2) {
		// basic
		// put numbers into a vector. O(m) + O(n)
		// compare two vector. O(m + n)
		// total: O(m+n)

		std::vector<int> num1 = getNumbers(version1);
		std::vector<int> num2 = getNumbers(version2);

		auto n1 = num1.size();
		auto n2 = num2.size();

		decltype(n1) i(0), j(0);
		while (i < n1 && i < n2 && (num1[i] == num2[i])) ++i;

		if (i < n1 && i < n2) {
			// break because of num1[i] != num2[i];
			return (num1[i] > num2[i] ? 1 : -1);
		}
		else {
			// break becuase of i exceeds range.
			if (n1 == n2) {
				return 0;
			}
			else {
				if (n1 > n2) {
					for (decltype(n1) j = i + 1; j<n1; ++j) {
						if (num1[j] > 0) {
							return 1;
						}
					}
					return 0;
				}
				else {
					for (decltype(n1) j = i + 1; j<n2; ++j) {
						if (num2[j] > 0) {
							return -1;
						}
					}
					return 0;
				}
			}
		}

		return 0;



		// int part11 = toInt(version1.substr(version1.find_first_of('.')));
		// int part21 = toInt(version1.substr(version2.find_first_of('.')));
		// if (part11 > part21) {
		// return 1;
		// }
		// else if (part11 < part21) {
		// return -1;
		// }
		// else {
		// int part21 = toInt(version1.substr(version1.find_first_of('.')));
		// int part22 = toInt(version1.substr(version2.find_first_of('.')));
		// if (part21 > part22) {
		// return 1;
		// }
		// else if (part21 < part22) {
		// return -1;
		// }
		// else {
		// return 0;
		// }
		// }


	}
};

NS_END(compare_version)
NS_END(elloop)