#include "ctr_dtr_assignment_op.h"
#include <string>

NS_BEGIN(elloop);
<<<<<<< HEAD
BEGIN_TEST(CopyControl, AssignmentDontworkWithConstAndRef, @)
  using std::string;
  string str("he");
  HasRefAndConst hr(str);
  HasRefAndConst hrCopy(hr);
  EXPECT_EQ(hr.i_, hrCopy.i_);
  EXPECT_EQ(0, hr.i_);
=======
BEGIN_TEST(CopyControl, AssignmentDontworkWithConstAndRef, @);
using std::string;
string str("he");
HasRefAndConst hr(str);
HasRefAndConst hrCopy(hr);
EXPECT_EQ(hr.i_, hrCopy.i_);
EXPECT_EQ(0, hr.i_);
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

HasRefAndConst hrCopy2 = hrCopy; // call copy constructor not the assignment op.

<<<<<<< HEAD
  string str2("she");
  HasRefAndConst hrByAssignment(str2);
  //hrByAssignment = hr; // error: “operator = ”函数在“elloop::HasRefAndConst”中不可用
END_TEST
=======
string str2("she");
HasRefAndConst hrByAssignment(str2);
//hrByAssignment = hr; // error: “operator = ”函数在“elloop::HasRefAndConst”中不可用

END_TEST;
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

NS_END(elloop);