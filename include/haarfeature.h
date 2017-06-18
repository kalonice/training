#ifndef INCLUDE_HAARFEATURE_H_
#define INCLUDE_HAARFEATURE_H_
#include <vector>

const int defaultWidth = 2;
const int defaultHeight = 2;
const int defaultScale = 1;
const int defaultType = 0;
const int defaultNumTypes = 7;

class Point {
 private:
  int x;
  int y;

 public:
  Point(int new_x = 0, int new_y = 0) : x(new_x), y(new_y) {};
  virtual int getX() const;
  virtual int getY() const;
  virtual Point& operator=(Point newPoint);
  virtual ~Point() {};
};

class Size {
 private:
  int width;
  int height;

 public:
  Size(int new_width = defaultWidth, int new_height = defaultHeight) :
       width(new_width), height(new_height) {};
  virtual int get_width() const;
  virtual int get_height() const;
  virtual Size& operator*(int value);
  virtual Size& operator=(Size newSize);
  virtual ~Size() {};
};

class HaarFeature {
 private:
  Point point;
  int type;  // amount of types' Haar features is from 0 to 6
  int scale;
  bool rotate;
  Size size;
  Point blackPoint;
  Size blackSize;

 public:
    HaarFeature(Point newPoint = Point(),
                int newType = defaultType, int newScale = defaultScale,
                bool newRotate = false) : point(newPoint), type(newType), scale(newScale), rotate(newRotate) {
      switch (newType) {
        case 0: {
          size = Size() * scale;
          blackPoint = Point(point.getX() + size.get_width() / 2, point.getY());
          blackSize = Size(size.get_width() / 2, size.get_height());
          break;
        }
        case 1: {
          size = Size() * scale;
          blackPoint = Point(point.getX(), point.getY() + size.get_height() / 2);
          blackSize = Size(size.get_width(), size.get_height() / 2);
          break;
        }
        case 2: {
          size = Size(3 * scale, 2 * scale);
          blackPoint = Point(point.getX() + size.get_width() / 3, point.getY());
          blackSize = Size(size.get_width() / 3, size.get_height());
          break;
        }
        case 3: {
          size = Size(2 * scale, 3 * scale);
          blackPoint = Point(point.getX(), point.getY() + size.get_height() / 3);
          blackSize = Size(size.get_width(), size.get_height() / 3);
          break;
        }
        case 4: {
          size = Size(defaultWidth * 2, defaultHeight) * scale;
          blackPoint = Point(point.getX() + size.get_width() / 4, point.getY());
          blackSize = Size(size.get_width() / 2, size.get_height());
          break;
        }
        case 5: {
          size = Size(defaultWidth, defaultHeight * 2) * scale;
          blackPoint = Point(point.getX(), point.getY() + size.get_height() / 4);
          blackSize = Size(blackPoint.getX(), size.get_height() / 2);
          break;
        }
        case 6: {
          size = Size(defaultWidth * 2, defaultHeight * 2) * scale;
          blackPoint = Point(point.getX() + size.get_width() / 4, point.getY() + size.get_height() / 4);
          blackSize = Size(size.get_width() / 2, size.get_height() / 2);
          break;
        }
        default: {
          size = Size() * scale;
          blackPoint = Point(point.getX() + size.get_width() / 2, point.getY());
          blackSize = Size(size.get_width() / 2, size.get_height());
          break;
        }
      }
    };
    virtual bool isRotated() const;
    virtual Point getPoint() const;
    virtual Size getSize() const;
    virtual Point getBlackPoint() const;
    virtual Size getBlackSize() const;
    virtual int getType() const;
    virtual ~HaarFeature() {};
};

class IntegralImage{
private:
  std::vector<std::vector<int>> imgIntegral;
  std::vector<std::vector<int>> imgIntegralRotate;
  std::vector<std::vector<int>> makeIntegralImg(std::vector<std::vector<int>>);

public:
  IntegralImage(std::vector<std::vector<int>> newImg) {
    imgIntegral = std::move(makeIntegralImg(newImg));
    imgIntegralRotate = std::move(makeIntegralImg(newImg));  // !!Wrong
  };
  int getImgWidth() const;
  int getImgHeight() const;
  std::vector<std::vector<int>> getImg() const;
};

HaarFeature* createRandom(IntegralImage);
HaarFeature* createDefault();
HaarFeature* createSpecific(IntegralImage, Point, int, int, bool);

#endif  // INCLUDE_HAARFEATURE_H_
