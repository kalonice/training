#ifndef INCLUDE_MATHOPERATIONS_H_
#define INCLUDE_MATHOPERATIONS_H_

#include <string>
#include <memory>
#include <stack>
#include <utility>
#include "./mybiginteger.h"

namespace mycalc {

/**
 * приоритет для выполнения математических операций.
 * OPEN_PARENTHESIS и CLOSE_PARENTHESIS имеют различные приоритеты
 * для возможности их различения
 */

enum OperationPriority {
  MULTIPLY = 300,
  MINUS = 200,
  PLUS = 200,
  OPEN_PARENTHESIS = 100,
  CLOSE_PARENTHESIS = 50
};

/**
 * Интерфейс базового класса для математических операций
 */

class IOperation : public IBaseElement {
 public:
  static std::unique_ptr<IOperation> create(const char &operation);
  virtual OperationPriority getPriority() const = 0;
  virtual ~IOperation() {}
};

/**
 * Класс для математической операции '+'
 */
class OperationPlus : public IOperation {
 public:
  /**
   *
   * @return Возвращает приоритет математической операции - PLUS типа OperationPriority
   */
  OperationPriority getPriority() const override;
  /**
   *
   * @param rpn_stack Стек с числами над которыми выполняется операция '+',
   * результат выполнения операции помещается наверх стека
   * @return Возвращает всегда true
   */
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  /**
   * Деструктор
   */
  ~OperationPlus() {}
};

/**
 * Класс для математической операции '-'
 */
class OperationMinus : public IOperation {
 public:
  /**
   *
   * @return Возвращает приоритет математической операции - MINUS типа OperationPriority
   */
  OperationPriority getPriority() const override;
  /**
   *
   * @param rpn_stack Стек с двумя числами над которыми выполняется операция '-',
   * результат выполнения операции помещается наверх стека
   * @return Возвращает всегда true
   */
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  /**
   * Деструктор
   */
  ~OperationMinus() {}
};

/**
 * Класс для математической операции '*'
 */
class OperationMultiple : public IOperation {
 public:
  /**
   *
   * @return Возвращает приоритет математической операции - MULTIPLY типа OperationPriority
   */
  OperationPriority getPriority() const override;
  /**
   *
   * @param rpn_stack Стек с двумя числами над которыми выполняется операция '*',
   * результат выполнения операции помещается наверх стека
   * @return Возвращает всегда true
   */
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  /**
   * Деструктор
   */
  ~OperationMultiple() {}
};

/**
 * Класс для математической операции '('
 */
class OperationParenthOpen : public IOperation {
 public:
  /**
   *
   * @return Возвращает приоритет математической операции - OPEN_PARENTHESIS типа OperationPriority
   */
  OperationPriority getPriority() const override;
  /**
   *
   * @param rpn_stack Стек с двумя числами над которыми выполняется операция
   * @return Возвращает всегда true
   */
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  /**
   * Деструктор
   */
  ~OperationParenthOpen() {}
};

/**
 * Класс для математической операции '('
 */
class OperationParenthClose : public IOperation {
 public:
  /**
   *
   * @return Возвращает приоритет математической операции - CLOSE_PARENTHESIS типа OperationPriority
   */
  OperationPriority getPriority() const override;
  /**
   *
   * @param rpn_stack Стек с двумя числами над которыми выполняется операция
   * @return Возвращает всегда true
   */
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  /**
   * Деструктор
   */
  ~OperationParenthClose() {}
};

}  // namespace mycalc

#endif  // INCLUDE_MATHOPERATIONS_H_
