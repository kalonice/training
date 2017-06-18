#include "gtest/gtest.h"
#include <haarfeature.h>
#include <vector>
#include <iostream>

TEST(CreateHaarFeature, CanCreateHaarFeature) {
  std::vector<std::vector<int>> testImg(50, std::vector<int>(50));
  IntegralImage img(testImg);
  HaarFeature* haar0 = createDefault();
  HaarFeature* haar1 = createSpecific(img, Point(2,3), 1, 2, false);
  HaarFeature* haar2 = createRandom(img);
  EXPECT_EQ(haar0->getPoint().getX(), 0);
  EXPECT_EQ(haar0->getPoint().getY(), 0);
  int a = haar2->getType();
  auto b = haar1->getPoint();
  auto c = haar2->getSize();
  std::cout << img.getImgWidth() << ", type = " << a << "\n";
  std::cout << "x = " << haar2->getPoint().getX() << ", y = " << haar2->getPoint().getY() << "\n";
  std::cout << "width = " << haar2->getSize().get_width() << ", height = " << haar2->getSize().get_height() << "\n";
}
