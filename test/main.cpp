#include <vector>
#include <iostream>
#include "../3rdparty/gtest/googletest/include/gtest/gtest.h"
#include "../include/example.h"
#include "../include/myinteger.h"

int main(int ac, char* av[]) {
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
