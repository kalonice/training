#ifndef INCLUDE_MYINTEGER_H_
#define INCLUDE_MYINTEGER_H_
#include <string>
#include <stack>
#include <memory>

// const char* ZERO_INTEGER_ = "0";
const char MINUS = '-';

class Integer;

class IBaseElement {
 public:
  virtual bool apply(std::stack<Integer*>* rpn_stack) = 0;
  virtual ~IBaseElement() {}
};

class IOperation : public IBaseElement {
 public:
  static std::shared_ptr<IOperation> create(const char& operation);
  virtual int getPriority() const = 0;  // step 100,200,300...
  virtual ~IOperation() {}
};

class Integer : public IBaseElement {
 public:
  explicit Integer(const std::string& val = "0", const bool& is_negative = false);
  Integer(const Integer&);
  Integer(const Integer&&);
  Integer operator+(const Integer&);
  Integer operator-(const Integer&);
  Integer operator*(const Integer&);
  Integer& operator=(const Integer&);
  Integer& operator+=(const Integer&);
  Integer& operator-=(const Integer&);
  Integer& operator*=(const Integer&);
  bool apply(std::stack<Integer*>* rpn_stack) override;
  bool operator==(const Integer&) const;
  bool operator!=(const Integer&) const;
  bool operator>(const Integer&) const;
  bool operator<(const Integer&) const;
  friend std::ostream& operator<<(std::ostream&, const Integer&);
  bool IsNegative() const;  // ?
  std::string GetValue() const;
  void Print() const;
  ~Integer() {}

 private:
  std::string value;  // хранимое число
  bool is_negative;   // флаг отрицательного числа
};

class OperationPlus : public IOperation {
 public:
  int getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationPlus() {}
};

class OperationMinus : public IOperation {
 public:
  int getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationMinus() {}
};

class OperationMultiple : public IOperation {
 public:
  int getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationMultiple() {}
};

class OperationParenthOpen : public IOperation {
 public:
  int getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationParenthOpen() {}
};

class OperationParenthClose : public IOperation {
 public:
  int getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationParenthClose() {}
};

#endif  // INCLUDE_MYINTEGER_H_
