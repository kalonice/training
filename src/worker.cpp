#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <list>
#include "../include/myinteger.h"
#include "../include/worker.h"

Worker::Worker(const std::string& new_expression) : expression(new_expression),
                                             expression_is_valid(true), overflow(false) {
}

static bool is_math_operation(const char& symbol_operation) {
  if (symbol_operation == '+' || symbol_operation == '-' || symbol_operation == '*') {
    return true;
  } else {
    return false;
  }
}

static bool is_parenthesis(const char &symbol_operation) {
  if (symbol_operation == '(' || symbol_operation == ')') {
    return true;
  } else {
    return false;
  }
}

void Worker::moveOperationToRpn() {
  rpn.push_back(std::move(operations.top()));
  operations.pop();
}

void Worker::ProcessOperationStack(std::unique_ptr<IOperation> input_operator) {
  bool is_open_parenthesis = input_operator->getPriority() == OperationPriority::OPEN_PARANTHESIS;
  bool is_close_parenthesis = input_operator->getPriority() == OperationPriority::CLOSE_PARANTHESIS;

  if (is_close_parenthesis) {
    while (!operations.empty() && operations.top()->getPriority() != OperationPriority::OPEN_PARANTHESIS) {
      moveOperationToRpn();
    }
    if (operations.empty()) {
      expression_is_valid = false;
      return;
    }
    if (!operations.empty() && operations.top()->getPriority() == OperationPriority::OPEN_PARANTHESIS) {
      operations.pop();
    }
  } else if (is_open_parenthesis) {
    operations.push(std::move(input_operator));
  } else {
    while (!operations.empty() && input_operator->getPriority() <= operations.top()->getPriority()) {
      moveOperationToRpn();
    }
    operations.push(std::move(input_operator));
  }
}

std::unique_ptr<Integer> Worker::Calculate() {
  std::stack<Integer*> calc;
  for (size_t i = 0; i < rpn.size(); ++i) {
    rpn[i]->apply(&calc);
  }

  if (calc.size() != 1 || calc.top()->IsOverflow()) {
    return std::make_unique<Integer>();
  } else {
    return std::make_unique<Integer>(*calc.top());
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
        rpn.push_back(std::make_unique<Integer>());
        prev_is_operation = false;
      }
      first_symbol = false;
    }

    // check if operation is valid
    if (i + 1 < expression.size() && !prev_is_operation && is_math_operation(expression[i])) {
      prev_is_operation = true;
      ProcessOperationStack(IOperation::create(expression[i]));
      ++i;
    } else if (i + 1 < expression.size() && prev_is_operation && is_math_operation(expression[i])) {
      expression_is_valid = false;
      break;
    } else if (i + 1 < expression.size() && !is_math_operation(expression[i]) &&
                                            !is_parenthesis(expression[i]) &&
                                            !isdigit(expression[i])) {
      expression_is_valid = false;
      break;
    }

    // check the last symbol
    if (i == expression.size() - 1 && !isdigit(expression[i]) && expression[i] != ')') {
      expression_is_valid = false;
      break;
    }

    if (is_parenthesis(expression[i])) {
      ProcessOperationStack(IOperation::create(expression[i]));
      if (!expression_is_valid) {
        break;
      }
      ++i;
    }

    std::string tmp_num;
    while (i < expression.size() && isdigit(expression[i])) {
      tmp_num += expression[i];
      ++i;
    }

    if (Integer::IsOverflow(tmp_num)) {
      overflow = true;
      break;
    }

    if (tmp_num.size() > 0 && prev_is_operation) {
      rpn.push_back(std::make_unique<Integer>(std::move(tmp_num)));
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
    moveOperationToRpn();
  }
}

std::unique_ptr<Integer> Worker::CalcExpression() {
  ParseExpression();
  if (!expression_is_valid || overflow) {
    return std::make_unique<Integer>();
  }

  return std::move(Calculate());
}
