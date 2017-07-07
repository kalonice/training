#include <string>
#include <algorithm>
#include "../include/myinteger.h"

Integer::Integer(std::string new_value, bool new_negate) :
        value(new_value), negative(new_negate) {
  if (negative) {
    minus = '-';
  }
}

std::string Integer::GetString() const {
  return this->value;
}

bool Integer::IsNegative() const {
  return negative;
}

std::string Integer::AddStrings(const std::string& num1, const std::string& num2) {
  char up = '0';
  std::string res;
  char n1, n2, tmp;
  int i = static_cast<int>(num1.size()) - 1, j = static_cast<int>(num2.size()) - 1;

  while (i >= 0 || j >= 0) {
    if (i < 0)
      n1 = 0;
    else
      n1 = static_cast<char>(num1[i] - '0');

    if (j < 0)
      n2 = 0;
    else
      n2 = static_cast<char>(num2[j] - '0');

    tmp = static_cast<char>(n1 + n2 + up);

    if (tmp > '9') {
      up = '1';
      tmp = static_cast<char>(tmp - 10);
    } else {
      up = '0';
    }
    res = tmp + res;
    i--;
    j--;
  }
  if (up > '0') {
    res = up + res;
  }
  return res;
}

std::string Integer::MulStrings(const std::string& num1, const std::string& num2) {
  char a = 0, b = 0;
  std::string res, tmp;

  if (num1 == "0" || num2 == "0") {
    res = "0";
    return res;
  }

  for (int i = static_cast<int>(num2.size() - 1); i >= 0; i--) {
    for (int j = static_cast<int>(num1.size()) - 1; j >= 0; j--) {
      a = static_cast<char>((num1[j] - '0') * (num2[i] - '0') + b);

      b = a / 10;
      a = a % 10;
      a = static_cast<char>(a + '0');
      tmp += a;
    }
    if (b != 0) {
      b = static_cast<char>(b + '0');
      tmp += b;
    }
    b = 0;
    std::reverse(tmp.begin(), tmp.end());
    int k = static_cast<int>(num2.size() - 1 - i);
    while (k != 0) {
      tmp += '0';
      k--;
    }
    res = AddStrings(res, tmp);
    tmp = "";
  }
  return res;
}

std::string Integer::DedStrings(const std::string& num1, const std::string& num2) {
  // считаем, что num1 всегда > num2 (проверяем в вызывающей функции)
  char up = 0;
  std::string res;
  char n1, n2, tmp;
  int i = static_cast<int>(num1.size()) - 1, j = static_cast<int>(num2.size()) - 1;

  while (i >= 0 || j >= 0) {
    if (i < 0)
      n1 = 0;
    else
      n1 = static_cast<char>(num1[i] - '0');

    if (j < 0)
      n2 = 0;
    else
      n2 = static_cast<char>(num2[j] - '0');

    tmp = static_cast<char>(n1 - n2 - up + '0');

    if (tmp < '0') {
      up = 1;
      tmp = static_cast<char>(tmp + 10);
    } else {
      up = 0;
    }
    res += tmp;
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
    res = "0";
  }
  return res;
}

bool Integer::CmpStrings(const std::string& num1, const std::string& num2) {
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

bool Integer::operator==(const Integer& rval) {
  return value == rval.value;
}

bool Integer::operator!=(const Integer& rval) {
  return value != rval.value;
}

bool Integer::operator>(const Integer& rval) {
  return CmpStrings(value, rval.value);
}

bool Integer::operator<(const Integer& rval) {
  return CmpStrings(rval.value, value);
}

Integer Integer::operator+(const Integer& rval) {
  if (!negative && !rval.negative) {                       // if both values are positives
    return Integer(AddStrings(value, rval.value), false);
  } else if (!negative && rval.negative) {                 // if only rval is negative
    if (CmpStrings(value, rval.value)) {                   // if value > rval.value
      return Integer(DedStrings(value, rval.value), false);
    } else {                                               // if value < rval.value
      return Integer(DedStrings(rval.value, value), true);
    }
  } else if (negative && !rval.negative) {                 // if only value is negative
    if (CmpStrings(value, rval.value)) {                   // if value > rval.value
      return Integer(DedStrings(value, rval.value), true);
    } else {                                               // if value < rval.value
      return Integer(DedStrings(rval.value, value), false);
    }
  } else {                                                 // if both values are negatives
    return Integer(AddStrings(value, rval.value), true);
  }
}

Integer Integer::operator-(const Integer& rval) {
  if (!negative && !rval.negative) {                       // if both values are positives
    if (CmpStrings(value, rval.value)) {
      return Integer(DedStrings(value, rval.value), false);
    } else {
      return Integer(DedStrings(rval.value, value), true);
    }
  } else if (!negative && rval.negative) {                 // if only rval is negative
    return Integer(AddStrings(value, rval.value), false);
  } else if (negative && !rval.negative) {                 // if only value is negative
    return Integer(AddStrings(value, rval.value), true);
  } else {                                                 // if both values are negatives
    if (CmpStrings(value, rval.value)) {                   // if value > rval.value
      return Integer(DedStrings(value, rval.value), true);
    } else {                                               // if value < rval.value
      return Integer(DedStrings(rval.value, value), false);
    }
  }
}

Integer Integer::operator*(const Integer& rval) {
  if ((!negative && !rval.negative) || (negative && rval.negative)) {
    return Integer(MulStrings(value, rval.value), false);
  } else if ((!negative && rval.negative) || (negative && !rval.negative)) {
    return Integer(MulStrings(value, rval.value), true);
  }
  return Integer();
}

Integer& Integer::operator=(const Integer& rval) {
  value = rval.value;
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
  std::string s;
  if (rval.negative) {
    s += "-";
  }
  s += rval.value;
  outStream << s;
  return outStream;
}
