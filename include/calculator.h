#ifndef INCLUDE_CALCULATOR_H_
#define INCLUDE_CALCULATOR_H_
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <list>
#include <memory>
#include "./mybiginteger.h"
#include "./mathoperations.h"

namespace mycalc {
/**
 * Класс для обработки метематического выражения с "длинными" числами
 */
class Calculator {
 public:
  /**
   * Конструктор
   * @param input_expression входное математическое выражение с "длинными" числами
   */
  explicit Calculator(const std::string& input_expression);
  /**
   * Деструктор
   */
  ~Calculator() {}
  /**
   *
   * @return Результат вычисления выражения. В случае наличия недопустимого выражения или переполнения в ходе
   * обработки возвращает nullptr, в противном случае - указатель на "длинное" число типа BigInteger
   */
  std::unique_ptr<BigInteger> CalcExpression();  // вычисленеие выражения и запись результата

 private:
  void ParseExpression();  // создание обратной польской записи и анализ допустимости выражения
  std::unique_ptr<BigInteger> Calculate();  // получение результата из сформированной обратной польской записи
  void ProcessOperationStack(std::unique_ptr<IOperation> cur_operation);  // Обработка стека
  void moveOperationToRpn();  // функция обработки операций и помещения ее в обратную польскую запись

  std::string expression;  // входное выражение
  bool expression_is_valid;  // флаг валидности выражения
  bool overflow;  // флаг наличия переполнения
  std::vector<std::unique_ptr<IBaseElement>> rpn;  // массив для обратной польской записи
  std::stack<std::unique_ptr<IOperation>> operations;  // стек математических операций для обратной польской записи
};

}  // namespace mycalc

#endif  // INCLUDE_CALCULATOR_H_
