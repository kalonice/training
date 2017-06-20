#include <vector>
#include <iostream>
#include "gtest/gtest.h"
#include "./haarfeature.h"

namespace myHaar {

TEST(CreateHaarFeature, CanCreateHaarFeature) {
  std::vector<std::vector<int>> testImg(50, std::vector<int>(50));
  IntegralImage img(testImg);
  HaarFeature* haarCreater;
  HaarFeature* haar0 = haarCreater->createDefault();
  HaarFeature* haar1 = haarCreater->createSpecific(img, Point(2, 3), VERTICAL_2x2, 2, false);
  HaarFeature* haar2 = haarCreater->createRandom(img);
  HaarFeature* haar3 = haarCreater->createSpecific(img, Point(40, 10), VERTICAL_2x2, 10, false);
  auto a = haar2->getType();
  auto b = haar1->getPoint();
  auto c = haar2->getSize();
  std::cout << "type = " << a << "\n";
  std::cout << "x = " << haar2->getPoint().getX() << ", y = " << haar2->getPoint().getY() << "\n";
  std::cout << "width = " << haar2->getSize().getWidth() << ", height = " << haar2->getSize().getHeight() << "\n";

  EXPECT_EQ(haar0->getPoint().getX(), 0);
  EXPECT_EQ(haar0->getPoint().getY(), 0);
  EXPECT_EQ(haar1->getPoint().getY(), 3);
  EXPECT_EQ(haar1->getType(), VERTICAL_2x2);
  EXPECT_EQ(haar3, nullptr);
}

}  // namespace myHaar
