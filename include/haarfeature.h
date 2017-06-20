#ifndef INCLUDE_HAARFEATURE_H_
#define INCLUDE_HAARFEATURE_H_
#include <vector>

namespace myHaar {

enum haarFeatureType {HORIZONTAL_2x2, VERTICAL_2x2,
                      HORIZONTAL_3x2, VERTICAL_3x2,
                      HORIZONTAL_4x2, VERTICAL_4x2,
                      FOURSQUARE};

const haarFeatureType defaultType = HORIZONTAL_2x2;
const int defaultWidth = 2;
const int defaultHeight = 2;
const int defaultScale = 1;
const int defaultNumTypes = 7;
const int defaultRatio3 = 3;
const int defaultRatio4 = 4;

class Point {
 public:
  explicit Point(int new_x = 0, int new_y = 0);
  int getX() const;
  int getY() const;
  Point& operator=(const Point new_point);
  ~Point() {}

 private:
  int x;
  int y;
};

class Size {
 public:
  explicit Size(int = defaultWidth, int = defaultHeight);
  int getWidth() const;
  int getHeight() const;
  Size& operator*(int value);
  Size& operator=(const Size new_size);
  ~Size() {}

 private:
  int width;
  int height;
};


int verticalRatio(haarFeatureType);
int horizontalRatio(haarFeatureType);

class IntegralImage{
 public:
    explicit IntegralImage(std::vector<std::vector<int>> newImg);
    int getImgWidth() const;
    int getImgHeight() const;
    std::vector<std::vector<int>> getImg() const;

 private:
    std::vector<std::vector<int>> imgIntegral;
    std::vector<std::vector<int>> imgIntegralRotate45d;
    std::vector<std::vector<int>> makeIntegralImg(std::vector<std::vector<int>>);
};

class HaarFeature {
 public:
  bool isRotated() const;
  Point getPoint() const;
  Size getSize() const;
  Point getBlackPoint() const;
  Size getBlackSize() const;
  int getType() const;
  bool haarFeatureCreated() const;
  static HaarFeature* createDefault();
  static HaarFeature* createRandom(IntegralImage);
  static HaarFeature* createSpecific(IntegralImage, Point, haarFeatureType, int, bool);
  ~HaarFeature() {}

 private:
  HaarFeature(Point newPoint = Point(),
              haarFeatureType newType = defaultType,
              int newScale = defaultScale,
              bool newRotate = false);
  Point point;
  haarFeatureType type;
  int scale;
  bool rotate45d;
  Size size;
  Point blackPoint;
  Size blackSize;
  bool possibleToCreated;
};

}  // namespace myHaar

#endif  // INCLUDE_HAARFEATURE_H_
