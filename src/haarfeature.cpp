#include <vector>
#include <algorithm>
#include <random>
#include "haarfeature.h"

int Point::getX() const {
  return Point::x;
}
int Point::getY() const {
  return Point::y;
}

Point& Point::operator=(Point newPoint){
  Point::x = newPoint.x;
  Point::y = newPoint.y;
  return *this;
}

int Size::get_width() const {
  return Size::width;
}
int Size::get_height() const {
  return Size::height;
}

Size& Size::operator*(int value) {
  Size::width *= value;
  Size::height *= value;
  return *this;
}

Size& Size::operator=(Size newSize) {
  Size::width = newSize.width;
  Size::height = newSize.height;
  return *this;
}

bool HaarFeature::isRotated() const{
  return HaarFeature::rotate;
}

Point HaarFeature::getPoint() const{
  return HaarFeature::point;
}

Size HaarFeature::getSize() const{
  return HaarFeature::size;
}

Point HaarFeature::getBlackPoint() const{
  return HaarFeature::blackPoint;
}

Size HaarFeature::getBlackSize() const{
  return HaarFeature::blackSize;
}

int HaarFeature::getType() const{
  return HaarFeature::type;
}

int IntegralImage::getImgHeight() const{
  return static_cast<int>(IntegralImage::imgIntegral.size());
}

int IntegralImage::getImgWidth() const{
  if (imgIntegral.size() != 0){
    return static_cast<int>(IntegralImage::imgIntegral[0].size());
  } else{
    return 0;
  }
}

std::vector<std::vector<int>> IntegralImage::getImg() const{
  return imgIntegral;
}

std::vector<std::vector<int>> IntegralImage::makeIntegralImg(std::vector<std::vector<int>> newImg){
  std::vector<std::vector<int>> imgIntegral(newImg.size(), std::vector<int>(newImg[0].size()));

  int height = static_cast<int>(imgIntegral.size());
  int width = static_cast<int>(imgIntegral[0].size());

  imgIntegral[0][0] = newImg[0][0];

  for (int x = 1; x < width; ++x){
    imgIntegral[0][x] = imgIntegral[0][x-1] + newImg[0][x];
  }
  for (int y = 1; y < height; ++y){
    imgIntegral[y][0] = imgIntegral[y-1][0] + newImg[y][0];
  }
  for (int x = 1; x < width; ++x){
    for (int y = 1; y < height; ++y){
      imgIntegral[y][x] = newImg[y][x] + imgIntegral[y][x-1] + imgIntegral[y-1][x] - imgIntegral[y-1][x-1];
    }
  }
  return imgIntegral;
}

HaarFeature* createDefault(){
  return new HaarFeature();
}

HaarFeature* createSpecific(IntegralImage img, Point p, int type, int scale, bool rotate){
  if (p.getX() + defaultWidth * scale < img.getImgWidth() &&
      p.getY() + defaultHeight * scale >= img.getImgHeight()) {
    scale = (img.getImgHeight() - p.getY()) / defaultHeight;
  } else if(p.getX() + defaultWidth * scale >= img.getImgWidth() &&
            p.getY() + defaultHeight * scale < img.getImgHeight()){
    scale = (img.getImgWidth() - p.getX()) / defaultWidth;
  } else{
    scale = std::min((img.getImgHeight() - p.getY()) / defaultHeight,
                     (img.getImgWidth() - p.getX()) / defaultWidth);
  }

  if (scale <= 0){
    return new HaarFeature();
  } else {
    return new HaarFeature(p, type, scale, rotate);
  }
}

HaarFeature* createRandom(IntegralImage img){
  std::random_device rnd;
  int type = std::abs(static_cast<int>(rnd())) % defaultNumTypes;
  int scale = 0;
  Point p;

  while (scale == 0){
    int pointX = std::max(std::abs(static_cast<int>(rnd())) % img.getImgWidth() - defaultWidth, 0);
    int pointY = std::max(std::abs(static_cast<int>(rnd())) % img.getImgHeight() - defaultHeight, 0);
    p = Point(pointX, pointY);

    int max_scale = std::min((img.getImgHeight() - p.getY()) / defaultHeight,
                             (img.getImgWidth() - p.getX()) / defaultWidth);
    scale = std::abs(static_cast<int>(rnd())) % (max_scale);
  }
  bool rotate = static_cast<bool>(rnd() % 2);

  return new HaarFeature(p, type, scale, rotate);
}
