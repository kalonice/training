#include <vector>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <memory>
#include "../3rdparty/gtest/googletest/include/gtest/gtest.h"
#include "../include/mybiginteger.h"
#include "../include/mathoperations.h"
#include "../include/calculator.h"

TEST(RPN_1, Is_RPN_1_Correct) {
  std::string exp = "-12+8-2*6 *( 9-3*6)*5-7+(2 - 1) +  99";
  std::cout << "input expression#1: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#1: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "629");
}

TEST(RPN_2, Is_RPN_2_Correct) {
  std::string exp = "-12";
  std::cout << "\ninput expression#2: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#2: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "-12");
}

TEST(RPN_3, Is_RPN_3_Correct) {
  std::string exp = "0";
  std::cout << "\ninput expression#3: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#3: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "0");
}

TEST(RPN_4, Is_RPN_4_Correct) {
  std::string exp = "1 + 2";
  std::cout << "\ninput expression#4: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#4: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "3");
}

TEST(RPN_5, Is_RPN_5_Correct) {
  std::string exp = "6-5 +2";
  std::cout << "\ninput expression#5: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#5: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "3");
}

TEST(RPN_6, Is_RPN_6_Correct) {
  std::string exp = "-1*10-10";
  std::cout << "\ninput expression#6: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#6: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "-20");
}

TEST(RPN_7, Is_RPN_7_Correct) {
  std::string exp = "-1*10--10";
  std::cout << "\ninput expression#7: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#7: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_8, Is_RPN_8_Correct) {
  std::string exp = "-2*10-(-10)";
  std::cout << "\ninput expression#8: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#8: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "-10");
}

TEST(RPN_9, Is_RPN_9_Correct) {
  std::string exp = "(-2*10-(-10))";
  std::cout << "\ninput expression#9: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#9: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "-10");
}

TEST(RPN_10, Is_RPN_10_Correct) {
  std::string exp = "(-2*10-(-10))k";
  std::cout << "\ninput expression#10: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#10: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_11, Is_RPN_11_Correct) {
  std::string exp = "(((-2)))";
  std::cout << "\ninput expression#11: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#11: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "-2");
}

TEST(RPN_12, Is_RPN_12_Correct) {
  std::string exp = "((()))";
  std::cout << "\ninput expression#12: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#12: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_13, Is_RPN_13_Correct) {
  std::string exp = "(-2*10-(-10)))";
  std::cout << "\ninput expression#13: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#13: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_14, Is_RPN_14_Correct) {
  std::string exp = "+(-2*10-(-10))";
  std::cout << "\ninput expression#14: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#14: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_15, Is_RPN_15_Correct) {
  std::string exp = "0   +   (   -  2 *   10-(-    10)    )    ";
  std::cout << "\ninput expression#15: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#15: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "-10");
}

TEST(RPN_16, Is_RPN_16_Correct) {
  std::string exp = "-(-2*10-(-10))";
  std::cout << "\ninput expression#16: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#16: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "10");
}

TEST(RPN_17, Is_RPN_17_Correct) {
  std::string exp = "-";
  std::cout << "\ninput expression#17: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#17: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_18, Is_RPN_18_Correct) {
  std::string exp = "aaaaa + bbbbb";
  std::cout << "\ninput expression#18: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#18: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "Invalid expression");
}

TEST(RPN_19, Is_RPN_19_Correct) {
  std::string exp = "-(8) * (-8)";
  std::cout << "\ninput expression#19: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#19: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "64");
}

TEST(RPN_20, Is_RPN_20_Correct) {
  std::string exp = "5 * 10000000000000000000000000000000000000000000000000000000";
  std::cout << "\ninput expression#20: " << exp << "\n";
  mycalc::Calculator work(exp);
  auto output = work.CalcExpression();
  std::cout << "answer#20: " << output->GetValue() << "\n";

  EXPECT_EQ(output->GetValue(), "50000000000000000000000000000000000000000000000000000000");
}
