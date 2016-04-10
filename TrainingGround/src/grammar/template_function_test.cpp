//#pragma once          warning: #pragma once in main file [-Wpragma-once-outside-header]

#include "grammar/template_function_test.h"

NS_BEGIN(elloop);
NS_BEGIN(template_test);

BEGIN_TEST(GrammarTest, TemplateFunctionTest, @@);

returnT(1);
returnT(1.1);
A a;
returnT<A>(a);

END_TEST;

NS_END(template_test);
NS_END(elloop);
