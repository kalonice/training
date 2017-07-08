#ifndef INCLUDE_MYINTEGER_H_
#define INCLUDE_MYINTEGER_H_
#include <string>

class Integer {
 public:
  explicit Integer(std::string = "0", bool = false);  // value is string, false = positive value
  // explicit Integer(const Integer&);
  Integer operator+(const Integer&);
  Integer operator-(const Integer&);
  Integer operator*(const Integer&);
  Integer& operator=(const Integer&);
  Integer& operator+=(const Integer&);
  Integer& operator-=(const Integer&);
  Integer& operator*=(const Integer&);
  // bool operator==(const Integer&);
  // bool operator!=(const Integer&);
  // bool operator>(const Integer&);
  // bool operator<(const Integer&);
  friend std::ostream& operator<<(std::ostream&, const Integer&);
  bool IsNegative() const;
  virtual bool isOperation() const;
  virtual std::string GetValue() const;
  virtual void Print() const;
  virtual ~Integer() {}

 protected:
  std::string value;

 private:
  bool negative;
  char minus;
  std::string AddStrings(const std::string&, const std::string&);
  std::string MulStrings(const std::string&, const std::string&);
  std::string DedStrings(const std::string&, const std::string&);
  bool CmpStrings(const std::string&, const std::string&);  // true if l > r
};

class Operation : public Integer {
 public:
  explicit Operation(std::string = "+");
  explicit Operation(const Operation&);
  explicit Operation(char = '+');
  bool isOperation() const;
  std::string getValue() const;
  bool operator==(const std::string&) const;
  bool operator!=(const std::string&) const;
  Operation& operator=(const Operation&);
  ~Operation() {}
};

#endif  // INCLUDE_MYINTEGER_H_
