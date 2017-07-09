#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <utility>
#include "../include/myinteger.h"

Integer::Integer(const std::string& new_value, const bool& new_negate) : value(new_value), is_negative(new_negate) {}

Integer::Integer(const Integer& new_obj) {
  value = new_obj.value;
  is_negative = new_obj.is_negative;
}

Integer::Integer(const Integer&& new_obj) {
  *this = std::move(new_obj);
}

std::string Integer::GetValue() const {
  return value;
}

bool Integer::IsNegative() const {
  return is_negative;
}

static std::string AddStrings(const std::string& num1, const std::string& num2) {
  char addition_one = '0';
  std::string res;
  char term1, term2, help_term;
  int i = static_cast<int>(num1.size()) - 1, j = static_cast<int>(num2.size()) - 1;

  while (i >= 0 || j >= 0) {
    if (i < 0) {
      term1 = 0;
    } else {
      term1 = static_cast<char>(num1[i] - '0');
    }

    if (j < 0) {
      term2 = 0;
    } else {
      term2 = static_cast<char>(num2[j] - '0');
    }

    help_term = static_cast<char>(term1 + term2 + addition_one);

    if (help_term > '9') {
      addition_one = '1';
      help_term = static_cast<char>(help_term - 10);
    } else {
      addition_one = '0';
    }

    res = help_term + res;
    i--;
    j--;
  }
  if (addition_one > '0') {
    res = addition_one + res;
  }
  return res;
}

static std::string MulStrings(const std::string& num1, const std::string& num2) {
  char term1 = 0, term2 = 0;
  std::string res, help_term;

  if (num1 == "0" || num2 == "0") {
    return "0";
  }

  for (int i = static_cast<int>(num2.size() - 1); i >= 0; --i) {
    for (int j = static_cast<int>(num1.size()) - 1; j >= 0; --j) {
      term1 = static_cast<char>((num1[j] - '0') * (num2[i] - '0') + term2);

      term2 = term1 / 10;
      term1 = term1 % 10;
      term1 = static_cast<char>(term1 + '0');
      help_term += term1;
    }
    if (term2 != 0) {
      term2 = static_cast<char>(term2 + '0');
      help_term += term2;
    }
    term2 = 0;
    std::reverse(help_term.begin(), help_term.end());
    int k = static_cast<int>(num2.size() - 1 - i);
    while (k != 0) {
      help_term += '0';
      k--;
    }
    res = AddStrings(res, help_term);
    help_term = "";
  }
  return res;
}

static std::string SubStrings(const std::string& num1, const std::string& num2) {
  // считаем, что num1 всегда > num2 (проверяем в вызывающей функции)
  char up = 0;
  std::string res;
  char term1, term2, help_term;
  int i = static_cast<int>(num1.size()) - 1, j = static_cast<int>(num2.size()) - 1;

  while (i >= 0 || j >= 0) {
    if (i < 0) {
      term1 = 0;
    } else {
      term1 = static_cast<char>(num1[i] - '0');
    }
    if (j < 0) {
      term2 = 0;
    } else {
      term2 = static_cast<char>(num2[j] - '0');
    }

    help_term = static_cast<char>(term1 - term2 - up + '0');

    if (help_term < '0') {
      up = 1;
      help_term = static_cast<char>(help_term + 10);
    } else {
      up = 0;
    }

    res += help_term;
    i--;
    j--;
  }
  int t = static_cast<int>(res.size()) - 1;
  int resize_res;
  while (t >= 0 && res[t] == '0') {
    ++resize_res;
    --t;
  }
  res.resize(res.size() - resize_res);
  std::reverse(res.begin(), res.end());
  if (res.size() == 0) {
    return "0";
  }
  return res;
}

static bool CmpStrings(const std::string& num1, const std::string& num2) {
  if (num1.size() > num2.size()) {
    return true;
  } else if (num1.size() == num2.size()) {
    for (size_t i = 0; i < num1.size(); ++i) {
      if (num1[i] > num2[i]) {
        return true;
      } else if (num1[i] < num2[i]) {
        return false;
      }
    }
  } else {
    return false;
  }
  return false;
}

bool Integer::operator==(const Integer& rval) const {
  return value == rval.value;
}

bool Integer::operator!=(const Integer& rval) const {
  return value != rval.value;
}

bool Integer::operator>(const Integer& rval) const {
  return CmpStrings(value, rval.value);
}

bool Integer::operator<(const Integer& rval) const {
  return CmpStrings(rval.value, value);
}

Integer Integer::operator+(const Integer& rval) {
  if (!is_negative && !rval.is_negative) {                       // if both values are positives
    return Integer(AddStrings(value, rval.value), false);
  } else if (!is_negative && rval.is_negative) {                 // if only rval is is_negative
    if (*this > rval) {                                    // if value > rval.value
      return Integer(SubStrings(value, rval.value), false);
    } else {                                               // if value < rval.value
      return Integer(SubStrings(rval.value, value), true);
    }
  } else if (is_negative && !rval.is_negative) {                 // if only value is is_negative
    if (*this > rval) {                                    // if value > rval.value
      return Integer(SubStrings(value, rval.value), true);
    } else {                                               // if value < rval.value
      return Integer(SubStrings(rval.value, value), false);
    }
  } else {                                                 // if both values are negatives
    return Integer(AddStrings(value, rval.value), true);
  }
}

Integer Integer::operator-(const Integer& rval) {
  if (!is_negative && !rval.is_negative) {                       // if both values are positives
    if (*this > rval) {
      return Integer(SubStrings(value, rval.value), false);
    } else {
      return Integer(SubStrings(rval.value, value), true);
    }
  } else if (!is_negative && rval.is_negative) {                 // if only rval is is_negative
    return Integer(AddStrings(value, rval.value), false);
  } else if (is_negative && !rval.is_negative) {                 // if only value is is_negative
    return Integer(AddStrings(value, rval.value), true);
  } else {                                                 // if both values are negatives
    if (*this > rval) {                                    // if value > rval.value
      return Integer(SubStrings(value, rval.value), true);
    } else {                                               // if value < rval.value
      return Integer(SubStrings(rval.value, value), false);
    }
  }
}

Integer Integer::operator*(const Integer& rval) {
  if ((!is_negative && !rval.is_negative) || (is_negative && rval.is_negative)) {
    return Integer(MulStrings(value, rval.value), false);
  } else if ((!is_negative && rval.is_negative) || (is_negative && !rval.is_negative)) {
    return Integer(MulStrings(value, rval.value), true);
  }
  return Integer();
}

Integer& Integer::operator=(const Integer& rval) {
  value = rval.value;
  is_negative = rval.is_negative;
  return *this;
}

Integer& Integer::operator+=(const Integer& rval) {
  *this = *this + rval;
  return *this;
}

Integer& Integer::operator-=(const Integer& rval) {
  *this = *this - rval;
  return *this;
}

Integer& Integer::operator*=(const Integer& rval) {
  *this = *this * rval;
  return *this;
}

std::ostream& operator<<(std::ostream& outStream, const Integer& rval) {
  std::string print_string;
  if (rval.is_negative) {
    print_string += "-";
  }
  print_string += rval.value;
  outStream << print_string;
  return outStream;
}

void Integer::Print() const {
  if (is_negative) {
    std::cout << MINUS;
  }
  std::cout << value;
}

bool Integer::apply(std::stack<Integer*>* rpn_stack) {
  rpn_stack->push(this);
  return true;
}

// OperationPlus' methods implementation

int OperationPlus::getPriority() const {
  return 200;
}

bool OperationPlus::apply(std::stack<Integer*>* rpn_stack) {
  Integer* num1 = rpn_stack->top();
  rpn_stack->pop();
  *rpn_stack->top() += *num1;
  return true;
}

// OperationMinus' methods implementation

int OperationMinus::getPriority() const {
  return 200;
}

bool OperationMinus::apply(std::stack<Integer*>* rpn_stack) {
  Integer* num1 = rpn_stack->top();
  rpn_stack->pop();
  *rpn_stack->top() -= *num1;
  return true;
}

// OperationMultiple' methods implementation

int OperationMultiple::getPriority() const {
  return 300;
}

bool OperationMultiple::apply(std::stack<Integer*>* rpn_stack) {
  Integer* num1 = rpn_stack->top();
  rpn_stack->pop();
  *rpn_stack->top() *= *num1;
  return true;
}

// OperationParenth' methods implementation

int OperationParenthOpen::getPriority() const {
  return 100;
}

bool OperationParenthOpen::apply(std::stack<Integer*>*) {
  return true;
}

// OperationParenth' methods implementation

int OperationParenthClose::getPriority() const {
  return 50;
}

bool OperationParenthClose::apply(std::stack<Integer*>*) {
  return true;
}

std::shared_ptr<IOperation> IOperation::create(const char& operation) {
  switch (operation) {
    case '+': {
      return std::make_shared<OperationPlus>();
    }
    case '-': {
      return std::make_shared<OperationMinus>();
    }
    case '*': {
      return std::make_shared<OperationMultiple>();
    }
    case '(': {
      return std::make_shared<OperationParenthOpen>();
    }
    case ')': {
      return std::make_shared<OperationParenthClose>();
    }
    default: {
      return nullptr;
    }
  }
}
