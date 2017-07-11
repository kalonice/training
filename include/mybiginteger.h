#ifndef INCLUDE_MYBIGINTEGER_H_
#define INCLUDE_MYBIGINTEGER_H_

#include <memory>
#include <stack>
#include <string>

namespace mycalc {

class BigInteger;

class IBaseElement {
 public:
  virtual bool apply(std::stack<BigInteger*>* rpn_stack) = 0;
  virtual ~IBaseElement() {}
};

class BigInteger : public IBaseElement {
 public:
  explicit BigInteger(const std::string& new_val = "0", const bool& is_negative = false);
  BigInteger(const BigInteger&);
  BigInteger(const BigInteger&&);
  BigInteger operator+(const BigInteger&);
  BigInteger operator-(const BigInteger&);
  BigInteger operator*(const BigInteger&);
  BigInteger& operator=(const BigInteger&);
  BigInteger& operator+=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  BigInteger& operator*=(const BigInteger&);
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;
  bool operator>(const BigInteger&) const;
  bool operator<(const BigInteger&) const;
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  bool IsNegative() const;
  std::string GetValue() const;
  bool IsOverflow() const;
  void Print() const;
  ~BigInteger() {}

  static bool IsOverflow(const std::string&);

 private:
  std::string value;  // хранимое число
  bool is_negative;   // флаг отрицательного числа
};

}  // namespace mycalc

#endif  // INCLUDE_MYBIGINTEGER_H_
