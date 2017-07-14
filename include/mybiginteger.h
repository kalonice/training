#ifndef INCLUDE_MYBIGINTEGER_H_
#define INCLUDE_MYBIGINTEGER_H_

#include <memory>
#include <stack>
#include <string>

namespace mycalc {

class BigInteger;

/**
 * Интерфейс базового класса для элементов выражения
 */
class IBaseElement {
 public:
  /**
   *
   * @param rpn_stack Стек с числами над которыми выполняется операция
   * @return Возвращает всегда true
   */
  virtual bool apply(std::stack<BigInteger*>* rpn_stack) = 0;
  /**
   * Деструктор
   */
  virtual ~IBaseElement() {}
};

/**
 * Класс для "длинных" чисел
 */
class BigInteger : public IBaseElement {
 public:
  /**
   *
   * @param new_val Абсолютное значение числа
   * @param is_negative Признак отрицательного числа (true - отрицательное)
   */
  explicit BigInteger(const std::string& new_val = "0", const bool& is_negative = false);
  /**
   * Конструктор копирования
   */
  BigInteger(const BigInteger&);
  /**
   * Конструктор перемещения
   */
  BigInteger(const BigInteger&&);
  /**
   *
   * @return Возвращает результат сложения двух "длинных" чисел
   */
  BigInteger operator+(const BigInteger&);
  /**
   *
   * @return Возвращает результат вычитанияя двух "длинных" чисел
   */
  BigInteger operator-(const BigInteger&);
  /**
   *
   * @return Возвращает результат умножения двух "длинных" чисел
   */
  BigInteger operator*(const BigInteger&);
  /**
   *
   * @return Присваивает полям this значения полей из rvalue
   */
  BigInteger& operator=(const BigInteger&);
  /**
   *
   * @return Присваивает полям this результат сложения this с rvalue
   */
  BigInteger& operator+=(const BigInteger&);
  /**
   *
   * @return Присваивает полям this результат вычитания this с rvalue
   */
  BigInteger& operator-=(const BigInteger&);
  /**
   *
   * @return Присваивает полям this результат умножения this с rvalue
   */
  BigInteger& operator*=(const BigInteger&);
  /**
   *
   * @param rpn_stack Стек с числами над которыми выполняются операции
   * @return Возвращает всегда true, действий не производит
   */
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  /**
   *
   * @return Возвращает true, если this == rvalue
   */
  bool operator==(const BigInteger&) const;
  /**
   *
   * @return Возвращает true, если this != rvalue
   */
  bool operator!=(const BigInteger&) const;
  /**
   *
   * @return Возвращает true, если this > rvalue
   */
  bool operator>(const BigInteger&) const;
  /**
   *
   * @return Возвращает true, если this < rvalue
   */
  bool operator<(const BigInteger&) const;
  /**
   *
   * @return Выводит "длинное" число в поток вывода
   */
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  /**
   *
   * @return Возвращает true, если число является отрицательным
   */
  bool isNegative() const;
  /**
   *
   * @return Возвращает "длинное" число (для отрицательного числа со знаком '-' вначале) в виде
   * строки типа std::string
   */
  std::string GetValue() const;
  /**
   *
   * @return Возвращает true, если количество десятичных разрядов в числе первышает 1048576
   */
  bool isOverflow() const;
  /*
   * Выводит на экран "длинное" число (для отрицательного числа со знаком '-' вначале)
   */
  void Print() const;
  /**
   * Деструктор
   */
  ~BigInteger() {}
  /**
   * @param В качестве "длинного" числа принимает строку типа std::string
   * @return Возвращает true, если длина строки первышает 1048576 символов
   */
  static bool isOverflow(const std::string & input_string);

 private:
  std::string value;  // хранимое число
  bool is_negative;   // флаг отрицательного числа
};

}  // namespace mycalc

#endif  // INCLUDE_MYBIGINTEGER_H_
