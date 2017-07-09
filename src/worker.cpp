#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <list>
#include "../include/myinteger.h"
#include "../include/worker.h"

Worker::Worker(std::string new_expression) : expression(new_expression),
                                             expression_is_valid(true), overflow(false),
                                             rpn(0), result("0") {
}

bool Worker::IsExpresionValid() const {
  return expression_is_valid;
}

bool Worker::IsOverflow(const Integer& obj) const {
  return obj.GetValue().size() > maxIntLength;
}

bool Worker::IsOverflow(const std::string& obj) const {
  return obj.size() > maxIntLength;
}

static bool is_math_operation(const char& symbol_operation) {
  if (symbol_operation == '+' || symbol_operation == '-' || symbol_operation == '*') {
    return true;
  } else {
    return false;
  }
}

static bool is_paranthesis(const char& symbol_operation) {
  if (symbol_operation == '(' || symbol_operation == ')') {
    return true;
  } else {
    return false;
  }
}

void Worker::putOperationToRpn() {
  auto operation_from_stack = operations.top();
  auto operation_into_base = std::dynamic_pointer_cast<IBaseElement>(operation_from_stack);
  rpn.push_back(operation_into_base);
}

void Worker::ProcessOperationStack(std::shared_ptr<IOperation> input_operator, const char& symbol_operation) {
  if (symbol_operation == ')') {
    while (!operations.empty() && operations.top()->getPriority() != 100) {   // пока не встретится '('
      putOperationToRpn();
      operations.pop();
    }
    if (operations.empty()) {
      expression_is_valid = false;
      return;
    }
    if (!operations.empty() && operations.top()->getPriority() == 100) {  // если встретилась '('
      operations.pop();
    }
  } else if (symbol_operation == '(') {
    operations.push(input_operator);
  } else {
    while (!operations.empty() && input_operator->getPriority() <= operations.top()->getPriority()) {
      putOperationToRpn();
      operations.pop();
    }
    operations.push(input_operator);
  }
}

void Worker::Calculate() {
  std::stack<Integer*> calc;
  for (size_t i = 0; i < rpn.size(); ++i) {
    rpn[i]->apply(&calc);
  }
  if (calc.empty()) {
    expression_is_valid = false;
  } else {
    result = *calc.top();
  }

  if (IsOverflow(result)) {
    overflow = true;
    result = Integer("Overflow");
  }

  calc.pop();  // Если осталось больше одного элемента, то ошибка

  if (!calc.empty()) {
    expression_is_valid = false;
  }
}

void Worker::ParseExpression() {
  bool first_symbol = true;
  bool prev_is_operation = true;
  size_t i = 0;

  while (i < expression.size() && expression_is_valid) {
    while (i < expression.size() && isspace(expression[i])) {  // skip spaces
      ++i;
    }

    // check the first symbol in expression
    if (i < expression.size() && first_symbol) {
      if (expression[i] != '-' && expression[i] != '(' && !isdigit(expression[i])) {
        expression_is_valid = false;
        break;
      } else if (expression[i] == '-') {
        rpn.push_back(std::make_shared<Integer>());
        prev_is_operation = false;
      }
      first_symbol = false;
    }

    // check if operation is valid
    if (i < expression.size() - 1 && !prev_is_operation && is_math_operation(expression[i])) {
      prev_is_operation = true;
      ProcessOperationStack(IOperation::create(expression[i]), expression[i]);
      ++i;
    } else if (i < expression.size() - 1 && prev_is_operation && is_math_operation(expression[i])) {
      expression_is_valid = false;
      break;
    } else if (i < expression.size() - 1 && !is_math_operation(expression[i]) &&
                                            !is_paranthesis(expression[i]) &&
                                            !isdigit(expression[i])) {
      expression_is_valid = false;
      break;
    }

    // check the last symbol
    if (i == expression.size() - 1 && !isdigit(expression[i]) && expression[i] != ')') {
      expression_is_valid = false;
      break;
    }

    if (is_paranthesis(expression[i])) {
      ProcessOperationStack(IOperation::create(expression[i]), expression[i]);
      if (expression_is_valid == false) {
        break;
      }
      ++i;
    }

    std::string tmp_num;
    while (i < expression.size() && isdigit(expression[i])) {
      tmp_num += expression[i];
      ++i;
    }

    if (IsOverflow(tmp_num)) {
      overflow = true;
      break;
    }

    if (tmp_num.size() > 0 && prev_is_operation) {
      rpn.push_back(std::make_shared<Integer>(tmp_num));
      prev_is_operation = false;
      tmp_num = "";
    } else if (tmp_num.size() > 0 && !prev_is_operation) {
      expression_is_valid = false;
      break;
    }
  }

  while (!operations.empty()) {
    if (operations.top()->getPriority() == 100) {
      expression_is_valid = false;
      break;
    }
    putOperationToRpn();
    operations.pop();
  }

  if (expression_is_valid == false) {
    result = Integer("Invalid expression");
    return;
  } else if (overflow) {
    result = Integer("Overflow");
    return;
  } else {
    Calculate();
  }
}

std::unique_ptr<Integer> Worker::CalcExpression() {
  ParseExpression();
  return std::make_unique<Integer>(result);
}
