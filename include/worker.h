#ifndef INCLUDE_WORKER_H_
#define INCLUDE_WORKER_H_
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <list>
#include <memory>
#include "../include/myinteger.h"

class Worker {
 public:
  explicit Worker(const std::string& input_expression);
  ~Worker() {}
  std::unique_ptr<Integer> CalcExpression();  // вычисленеие выражения и запись результата
  bool IsExpresionValid() const;  // Является ли обрабатываемое выражение допустимым

 private:
  void ProcessOperationStack(std::unique_ptr<IOperation> cur_operation, const char& sym_operation);  // Обработка стека
  void Calculate();  // получение результата из сформированной обратной польской записи
  void ParseExpression();  // создание обратной польской записи и анализ допустимости выражения
  bool IsOverflow(const Integer& number) const;  // Проверка на переполнение
  bool IsOverflow(const std::string& number_by_string) const;  // Проверка на переполнение
  void moveOperationToRpn();

  std::string expression;  // входное выражение
  bool expression_is_valid;  // флаг валидности выражения
  bool overflow;  // флаг наличия переполнения
  std::vector<std::unique_ptr<IBaseElement>> rpn;  // массив для обратной польской записи
  std::stack<std::unique_ptr<IOperation>> operations;  // стек математических операций для обратной польской записи
  Integer result;  // результат вычисления обратной польской записи
};

#endif  // INCLUDE_WORKER_H_
