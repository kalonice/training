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
 * для возможности их различения, т.к. метод getType() не предусмотрен
 */

enum OperationPriority {
  MULTIPLY = 300,
  MINUS = 200,
  PLUS = 200,
  OPEN_PARENTHESIS = 100,
  CLOSE_PARENTHESIS = 50
};

/**
 * Интерфейс базового класса для математических операций.
 * - Метод create() - фабрика создания математичекой операции, заданной
 * соответствующим символом.
 * - Метод getPriority() возвращает приоритет соответствующей операции
 */

class IOperation : public IBaseElement {
 public:
  static std::unique_ptr<IOperation> create(const char &operation);
  virtual OperationPriority getPriority() const = 0;
  virtual ~IOperation() {}
};

/**
 * Классы математических операций.
 * Метод apply() применяет соответствующую операция к двум верхним элементам
 * в стеке при расчете обратной польской последовательности
 */

class OperationPlus : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  ~OperationPlus() {}
};

class OperationMinus : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  ~OperationMinus() {}
};

class OperationMultiple : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  ~OperationMultiple() {}
};

class OperationParenthOpen : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  ~OperationParenthOpen() {}
};

class OperationParenthClose : public IOperation {
 public:
  OperationPriority getPriority() const override;
  bool apply(std::stack<BigInteger*>* rpn_stack) override;
  ~OperationParenthClose() {}
};

}  // namespace mycalc

#endif  // INCLUDE_MATHOPERATIONS_H_