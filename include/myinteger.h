#ifndef INCLUDE_MYINTEGER_H_
#define INCLUDE_MYINTEGER_H_

#include <memory>
#include <stack>
#include <string>

class Integer;

enum OperationPriority {
  MINUS = 200,
  PLUS = 200,
  MULTIPLY = 300,
  OPEN_PARENTHESIS = 100,
  CLOSE_PARENTHESIS = 50
};

class IBaseElement {
 public:
  virtual bool apply(std::stack<Integer*>* rpn_stack) = 0;
  virtual ~IBaseElement() {}
};

class IOperation : public IBaseElement {
 public:
  static std::unique_ptr<IOperation> create(const char& operation);
  virtual OperationPriority getPriority() const = 0;
  virtual ~IOperation() {}
};

class Integer : public IBaseElement {  // TODO(dsid): Rename to BigInteger
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
  bool IsNegative() const;
  std::string GetValue() const;
  bool IsOverflow() const;
  void Print() const;
  ~Integer() {}

  static bool IsOverflow(const std::string&);

 private:
  std::string value;  // хранимое число
  bool is_negative;   // флаг отрицательного числа
};

class OperationPlus : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationPlus() {}
};

class OperationMinus : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationMinus() {}
};

class OperationMultiple : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationMultiple() {}
};

class OperationParenthOpen : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationParenthOpen() {}
};

class OperationParenthClose : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<Integer*>* rpn_stack) override;
  ~OperationParenthClose() {}
};

#endif  // INCLUDE_MYINTEGER_H_
