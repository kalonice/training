#ifndef INCLUDE_MY_INTEGER_H
#define INCLUDE_MY_INTEGER_H
#include <string>

class BaseElement {
 public:
  BaseElement() {}
  virtual ~BaseElement() {}
};

class Integer : public BaseElement {
 public:
  Integer(std::string = "0", bool = false);  // value is string, false = positive value
  Integer operator+(const Integer&);
  Integer operator-(const Integer&);
  Integer operator*(const Integer&);
  Integer& operator=(const Integer&);
  Integer& operator+=(const Integer&);
  Integer& operator-=(const Integer&);
  Integer& operator*=(const Integer&);
  bool operator==(const Integer&);
  bool operator!=(const Integer&);
  bool operator>(const Integer&);
  bool operator<(const Integer&);
  friend std::ostream& operator<<(std::ostream&, const Integer&);
  bool IsNegative();
  std::string GetString();
  ~Integer() {}

 private:
  std::string value;
  bool negative;
  char minus;
  std::string AddStrings(const std::string&, const std::string&);
  std::string MulStrings(const std::string&, const std::string&);
  std::string DedStrings(const std::string&, const std::string&);
  bool CmpStrings(const std::string&, const std::string&);  // true if l > r
};



class Operation : public BaseElement {
 public:
  Operation(std::string = "+");
 private:
  std::string operation;
};

#endif  // INCLUDE_MY_INTEGER_H
