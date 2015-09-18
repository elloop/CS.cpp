#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include <string>
#include <cstring>

NS_BEGIN(elloop)
NS_BEGIN(zig_zag)

// P   A   H   N
// A P L S I I G
// Y   I   R
//
// convert("PAYPALISHIRING", 3) should return "
// PAHNAPLSIIGYIR".
// PAHNAPLSIIGYIR
// PAHNAPLSIIGYIR
//
// PAHNALLIIGGYIR
// PAHNALLIIGGYIR
//PAHNALIGYAIHRN
//  PAHNALIGYAIHRN 
class Solution {
public:
	std::string convert(std::string s, int nRows) {

		if (nRows == 1) {
			return s;
		}
		auto len = s.size();
		char * str = new char[len + 1];
		::memset(str, 0, len + 1);
		int cursor(0);
		decltype(len) j(0);
		for (int i = 0; i < nRows; ++i) {
			j = i;
			while (j < len) {
				// result.append(1, s[j]);
				str[cursor++] = s[j];
				if (i != 0 && i != (nRows - 1)) {
					if (j + 2 * (nRows - 1 - i) < len) {
						// result.append(1, s[j + 2 * (nRows - 1 - i)]);
						str[cursor++] = s[j + 2 * (nRows - 1 - i)];
					}
				}
				j += 2 * (nRows - 1);
			}
		}

		std::string result(str, str + len);
		delete[] str;
		return result;
	}

};

NS_END(zig_zag)
NS_END(elloop)