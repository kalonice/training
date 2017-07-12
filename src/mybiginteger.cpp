#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <utility>
#include "./mybiginteger.h"

namespace mycalc {

static const char MINUS_SYMBOL = '-';
static const size_t maxIntLength = 1048576;

BigInteger::BigInteger(const std::string &new_value, const bool &new_negate) :
        value(new_value), is_negative(new_negate) {}

BigInteger::BigInteger(const BigInteger &new_obj) {
  value = new_obj.value;
  is_negative = new_obj.is_negative;
}

BigInteger::BigInteger(const BigInteger &&new_obj) {
  value = std::move(new_obj.value);
  is_negative = new_obj.is_negative;
}

bool BigInteger::isOverflow() const {
  return value.size() > maxIntLength;
}

bool BigInteger::isOverflow(const std::string &str) {
  return str.size() > maxIntLength;
}

std::string BigInteger::GetValue() const {
  if (isNegative()) {
    return "-" + value;
  } else {
  return value;
  }
}

bool BigInteger::isNegative() const {
  return is_negative;
}

static std::string AddStrings(const std::string &num1, const std::string &num2) {
  char addition_one = '0';
  std::string res;
  char term1 = 0, term2 = 0, help_term = 0;
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

static std::string MulStrings(const std::string &num1, const std::string &num2) {
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

static std::string SubStrings(const std::string &num1, const std::string &num2) {
  // считаем, что num1 всегда > num2 (проверяем в вызывающей функции)
  char up = 0;
  std::string res;
  char term1, term2, help_term;
  int i = static_cast<int>(num1.size()) - 1;
  int j = static_cast<int>(num2.size()) - 1;

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
  int resize_res = 0;
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

static bool CmpStrings(const std::string &num1, const std::string &num2) {
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

bool BigInteger::operator==(const BigInteger &rval) const {
  return (value == rval.value && is_negative == rval.is_negative);
}

bool BigInteger::operator!=(const BigInteger &rval) const {
  return (value != rval.value || is_negative != rval.is_negative);
}

bool BigInteger::operator>(const BigInteger &rval) const {
  if (is_negative && rval.is_negative) {
    return CmpStrings(rval.value, value);
  } else if (is_negative && !rval.is_negative) {
    return false;
  } else if (!is_negative && rval.is_negative) {
    return true;
  } else {
    return CmpStrings(value, rval.value);
  }
}

bool BigInteger::operator<(const BigInteger &rval) const {
  if (is_negative && rval.is_negative) {
    return CmpStrings(value, rval.value);
  } else if (is_negative && !rval.is_negative) {
    return true;
  } else if (!is_negative && rval.is_negative) {
    return false;
  } else {
    return CmpStrings(rval.value, value);
  }
}

BigInteger BigInteger::operator+(const BigInteger &rval) {
  if (!is_negative && !rval.is_negative) {                       // if both values are positives
    return BigInteger(AddStrings(value, rval.value), false);
  } else if (!is_negative && rval.is_negative) {                 // if only rval is is_negative
    if (CmpStrings(value, rval.value)) {                         // if value > rval.value
      return BigInteger(SubStrings(value, rval.value), false);
    } else {                                                     // if value < rval.value
      return BigInteger(SubStrings(rval.value, value), true);
    }
  } else if (is_negative && !rval.is_negative) {                 // if only value is is_negative
    if (CmpStrings(value, rval.value)) {                         // if value > rval.value
      return BigInteger(SubStrings(value, rval.value), true);
    } else {                                                     // if value < rval.value
      return BigInteger(SubStrings(rval.value, value), false);
    }
  } else {                                                       // if both values are negatives
    return BigInteger(AddStrings(value, rval.value), true);
  }
}

BigInteger BigInteger::operator-(const BigInteger &rval) {
  if (!is_negative && !rval.is_negative) {                       // if both values are positives
    if (CmpStrings(value, rval.value)) {
      return BigInteger(SubStrings(value, rval.value), false);
    } else {
      return BigInteger(SubStrings(rval.value, value), true);
    }
  } else if (!is_negative && rval.is_negative) {                 // if only rval is is_negative
    return BigInteger(AddStrings(value, rval.value), false);
  } else if (is_negative && !rval.is_negative) {                 // if only value is is_negative
    return BigInteger(AddStrings(value, rval.value), true);
  } else {                                                       // if both values are negatives
    if (CmpStrings(value, rval.value)) {                         // if value > rval.value
      return BigInteger(SubStrings(value, rval.value), true);
    } else {                                                     // if value < rval.value
      return BigInteger(SubStrings(rval.value, value), false);
    }
  }
}

BigInteger BigInteger::operator*(const BigInteger &rval) {
  if ((!is_negative && !rval.is_negative) || (is_negative && rval.is_negative)) {
    return BigInteger(MulStrings(value, rval.value), false);
  } else if ((!is_negative && rval.is_negative) || (is_negative && !rval.is_negative)) {
    return BigInteger(MulStrings(value, rval.value), true);
  }
  return BigInteger();
}

BigInteger& BigInteger::operator=(const BigInteger &rval) {
  value = rval.value;
  is_negative = rval.is_negative;
  return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger &rval) {
  *this = *this + rval;
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger &rval) {
  *this = *this - rval;
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger &rval) {
  *this = *this * rval;
  return *this;
}

std::ostream &operator<<(std::ostream &outStream, const BigInteger &rval) {
  std::string print_string;
  if (rval.is_negative) {
    print_string += "-";
  }
  print_string += rval.value;
  outStream << print_string;
  return outStream;
}

void BigInteger::Print() const {
  if (is_negative) {
    std::cout << MINUS_SYMBOL;
  }
  std::cout << value;
}

bool BigInteger::apply(std::stack<BigInteger*>* rpn_stack) {
  rpn_stack->push(this);
  return true;
}

}  // namespace mycalc
