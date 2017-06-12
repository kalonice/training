#include "gtest/gtest.h"
#include <example.h>

TEST(Addition, CanAddTwoNumbers) {
  EXPECT_EQ(add(2, 2), 4);
  EXPECT_EQ(add(-2, 2), 0);
}
