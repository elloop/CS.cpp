#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(unicode_support)

// ------------------ 3 prefix ------------------
// 1. u8 : utf8 saved with char.
// 2. u : utf16 saved with char16_t.
// 3. U : utf32 saved with char32_t.

void test() {
#ifdef _MSC_VER
#else
	char utf8[] = u8"\u4F60\u597D\u554A";
	char16_t utf16[] = u"hello";
	char32_t utf32[] = U"hello = \u4F60\u597D\u554A";
#endif
}

NS_END(unicode_support)
NS_END(elloop)