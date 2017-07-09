#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <memory>
#include "../3rdparty/gtest/googletest/include/gtest/gtest.h"
#include "../include/myinteger.h"
#include "../include/worker.h"


TEST(RPN, Is_RPN_Correct) {
  std::string exp = "-12+8-2*6 *( 9-3*6)*5-7+(2 - 1) +  99";
  std::string exp2;
  exp2.resize(100);
  std::random_device rnd;
  for (size_t i = 0; i < 100; ++i) {
    char c = static_cast<char>(rnd() % 10 + '0');
    exp2[i] = c;
  }
  Worker work(exp);
  auto output = work.CalcExpression();
  std::string out1 = output->GetValue();

  EXPECT_EQ(out1, "629");
}
