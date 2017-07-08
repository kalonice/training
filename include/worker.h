#ifndef INCLUDE_WORKER_H_
#define INCLUDE_WORKER_H_
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <list>
#include <memory>
#include "../include/myinteger.h"

const size_t max_length_of_int = 1048576;

class Worker {
 public:
  explicit Worker(std::string = "");
  ~Worker() {}
  void CalcExpression(std::list<Integer>::iterator);  // вычисленеие выражения и запись результата
  std::string GetRPN();

 private:
  std::string expression;  // входное выражение
  bool expression_is_valid;  // флаг валидности выражения
  bool overflow;  // флаг наличия переполнения
  std::vector<Integer*> rpn;  // массив для обратной польской записи
  std::stack<Operation> operations;  // стек математических операций для обратной польской записи
  Integer result;  // результат вычисления обратной польской записи
  int Priority(const Operation&);  // Возвращает проиритет математической операции
  void ProcessOperationStack(const Operation&);  // Обработка стека математических операций
  void Calculate();  // получение результата из сформированной обратной польской записи
  void ParseExpression();  // создание обратной польской записи и анализ допустимости выражения
  bool IsExpresionValid();  // Является ли обрабатываемое выражение допустимым
  bool IsOverflow(const Integer&);  // Проверка на переполнение
  bool IsOverflow(const std::string&);  // Проверка на переполнение
};

#endif  // INCLUDE_WORKER_H_
