#include "grammar/override_member_function_test.h"

NS_BEGIN(elloop);
NS_BEGIN(override_test);

void Super::addChild(int i, int j /*= 0*/) {

}

BEGIN_TEST(GrammarTest, OverrideTest, @@);

D1 d;
//d.addChild(1, 2); // hide super's public function.

END_TEST;

NS_END(override_test);



NS_END(elloop);
