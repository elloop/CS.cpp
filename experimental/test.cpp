#include "gtest/gtest.h"
#include "simple.h"
#include <iostream>

TEST(Simple, Construct) 
{
  Simple s;
  EXPECT_EQ(10, s.getI());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
