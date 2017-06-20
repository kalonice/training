#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include "./haarfeature.h"

namespace myHaar {

Point::Point(int new_x, int new_y) : x(new_x), y(new_y) {}

int Point::getX() const {
  return Point::x;
}

int Point::getY() const {
  return Point::y;
}

Point& Point::operator=(const Point new_point) {
  Point::x = new_point.x;
  Point::y = new_point.y;
  return *this;
}

Size::Size(int new_width, int new_height) :
           width(new_width), height(new_height) {}

int Size::getWidth() const {
  return Size::width;
}

int Size::getHeight() const {
  return Size::height;
}

Size& Size::operator*(int value) {
  Size::width *= value;
  Size::height *= value;
  return *this;
}

Size& Size::operator=(const Size new_size) {
  Size::width = new_size.width;
  Size::height = new_size.height;
  return *this;
}

int verticalRatio(haarFeatureType type) {
  switch (type) {
    case HORIZONTAL_2x2: {
      return 2;
    }
    case VERTICAL_2x2: {
      return 2;
    }
    case HORIZONTAL_3x2: {
      return 2;
    }
    case VERTICAL_3x2: {
      return 3;
    }
    case HORIZONTAL_4x2: {
      return 2;
    }
    case VERTICAL_4x2: {
      return 4;
    }
    case FOURSQUARE: {
      return 2;
    }
    default: {
      return 2;
    }
  }
}

int horizontalRatio(haarFeatureType type) {
  switch (type) {
    case HORIZONTAL_2x2: {
      return 2;
    }
    case VERTICAL_2x2: {
      return 2;
    }
    case HORIZONTAL_3x2: {
      return 3;
    }
    case VERTICAL_3x2: {
      return 2;
    }
    case HORIZONTAL_4x2: {
      return 4;
    }
    case VERTICAL_4x2: {
      return 2;
    }
    case FOURSQUARE: {
      return 2;
    }
    default: {
      return 2;
    }
  }
}

bool HaarFeature::isRotated() const {
  return HaarFeature::rotate45d;
}

Point HaarFeature::getPoint() const {
  return HaarFeature::point;
}

Size HaarFeature::getSize() const {
  return HaarFeature::size;
}

Point HaarFeature::getBlackPoint() const {
  return HaarFeature::blackPoint;
}

Size HaarFeature::getBlackSize() const {
  return HaarFeature::blackSize;
}

int HaarFeature::getType() const {
  return HaarFeature::type;
}

bool HaarFeature::haarFeatureCreated() const {
  return HaarFeature::possibleToCreated;
}

IntegralImage::IntegralImage(std::vector<std::vector<int>> newImg) {
  IntegralImage::imgIntegral = std::move(IntegralImage::makeIntegralImg(newImg));
  IntegralImage::imgIntegralRotate45d = std::move(IntegralImage::makeIntegralImg(newImg));
}

int IntegralImage::getImgHeight() const {
  return static_cast<int>(IntegralImage::imgIntegral.size());
}

int IntegralImage::getImgWidth() const {
  if (imgIntegral.size() != 0) {
    return static_cast<int>(IntegralImage::imgIntegral[0].size());
  } else {
    return 0;
  }
}

std::vector<std::vector<int>> IntegralImage::getImg() const {
  return imgIntegral;
}

std::vector<std::vector<int>> IntegralImage::makeIntegralImg(std::vector<std::vector<int>> newImg) {
  std::vector<std::vector<int>> imgIntegral(newImg.size(), std::vector<int>(newImg[0].size()));

  int height = static_cast<int>(imgIntegral.size());
  int width = static_cast<int>(imgIntegral[0].size());

  imgIntegral[0][0] = newImg[0][0];

  for (int x = 1; x < width; ++x) {
    imgIntegral[0][x] = imgIntegral[0][x-1] + newImg[0][x];
  }
  for (int y = 1; y < height; ++y) {
    imgIntegral[y][0] = imgIntegral[y-1][0] + newImg[y][0];
  }
  for (int x = 1; x < width; ++x) {
    for (int y = 1; y < height; ++y) {
      imgIntegral[y][x] = newImg[y][x] + imgIntegral[y][x-1] + imgIntegral[y-1][x] - imgIntegral[y-1][x-1];
    }
  }
  return imgIntegral;
}

HaarFeature::HaarFeature(Point newPoint, haarFeatureType newType,
                         int newScale, bool newRotate) :
  point(newPoint), type(newType), scale(newScale), rotate45d(newRotate) {
    switch (newType) {
      case HORIZONTAL_2x2: {
        size = Size() * scale;
        blackPoint = Point(point.getX() + size.getWidth() / 2, point.getY());
        blackSize = Size(size.getWidth() / 2, size.getHeight());
        possibleToCreated = true;
        break;
      }
      case VERTICAL_2x2: {
        size = Size() * scale;
        blackPoint = Point(point.getX(), point.getY() + size.getHeight() / 2);
        blackSize = Size(size.getWidth(), size.getHeight() / 2);
        possibleToCreated = true;
        break;
      }
      case HORIZONTAL_3x2: {
        size = Size(horizontalRatio(type) * scale, verticalRatio(type) * scale);
        blackPoint = Point(point.getX() + size.getWidth() / 3, point.getY());
        blackSize = Size(size.getWidth() / 3, size.getHeight());
        possibleToCreated = true;
        break;
      }
      case VERTICAL_3x2: {
        size = Size(horizontalRatio(type) * scale, verticalRatio(type) * scale);
        blackPoint = Point(point.getX(), point.getY() + size.getHeight() / 3);
        blackSize = Size(size.getWidth(), size.getHeight() / 3);
        possibleToCreated = true;
        break;
      }
      case HORIZONTAL_4x2: {
        size = Size(horizontalRatio(type), verticalRatio(type)) * scale;
        blackPoint = Point(point.getX() + size.getWidth() / 4, point.getY());
        blackSize = Size(size.getWidth() / 2, size.getHeight());
        possibleToCreated = true;
        break;
      }
      case VERTICAL_4x2: {
        size = Size(horizontalRatio(type), verticalRatio(type)) * scale;
        blackPoint = Point(point.getX(), point.getY() + size.getHeight() / 4);
        blackSize = Size(blackPoint.getX(), size.getHeight() / 2);
        possibleToCreated = true;
        break;
      }
      case FOURSQUARE: {
        size = Size(defaultWidth * horizontalRatio(type), defaultHeight * verticalRatio(type)) * scale;
        blackPoint = Point(point.getX() + size.getWidth() / 4, point.getY() + size.getHeight() / 4);
        blackSize = Size(size.getWidth() / 2, size.getHeight() / 2);
        possibleToCreated = true;
        break;
      }
      default: {
        size = Size();
        blackPoint = Point();
        blackSize = Size();
        possibleToCreated = false;
        break;
      }
    }
  }

HaarFeature* HaarFeature::createDefault() {
  return new HaarFeature();
}

HaarFeature* HaarFeature::createSpecific(IntegralImage img, Point p,
                                         haarFeatureType type, int scale, bool rotate45d) {
  if (p.getX() + horizontalRatio(type) * scale >= img.getImgWidth() ||
      p.getY() + verticalRatio(type) * scale >= img.getImgHeight() ||
      type > FOURSQUARE) {
    return nullptr;
  } else {
    return new HaarFeature(p, type, scale, rotate45d);
  }
}

HaarFeature* HaarFeature::createRandom(IntegralImage img) {
  std::random_device rnd;
  haarFeatureType type = static_cast<haarFeatureType>(std::abs(static_cast<int>(rnd())) % defaultNumTypes);
  int scale = 0;
  Point p;
  int count = 0;

  while (scale == 0) {
    int pointX = std::max(std::abs(static_cast<int>(rnd())) % img.getImgWidth() - defaultWidth, 0);
    int pointY = std::max(std::abs(static_cast<int>(rnd())) % img.getImgHeight() - defaultHeight, 0);
    p = Point(pointX, pointY);

    int max_scale = std::min((img.getImgHeight() - p.getY()) / defaultHeight,
                             (img.getImgWidth() - p.getX()) / defaultWidth);
    scale = std::abs(static_cast<int>(rnd())) % (max_scale);
    ++count;
    if (count == 1000) {
      return nullptr;
    }
  }
  bool rotate45d = static_cast<bool>(rnd() % 2);

  return new HaarFeature(p, type, scale, rotate45d);
}
}  // namespace myHaar
