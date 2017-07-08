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
  rpn.reserve(expression.size());
}

int Worker::Priority(const Operation& input_operator) {
  if (input_operator.GetValue() == "*") {
    return 2;
  } else if (input_operator.GetValue() == "-" || input_operator.GetValue() == "+") {
    return 1;
  } else {
    return 0;
  }
}

bool Worker::IsExpresionValid() {
  return expression_is_valid;
}

bool Worker::IsOverflow(const Integer& obj) {
  return obj.GetValue().size() > max_length_of_int;
}

bool Worker::IsOverflow(const std::string& obj) {
  return obj.size() > max_length_of_int;
}

void Worker::ProcessOperationStack(const Operation& input_operator) {
  if (input_operator.GetValue() == ")") {
    while (!operations.empty() && operations.top() != "(") {
      rpn.push_back(new Operation(operations.top()));
      operations.pop();
    }
    if (operations.empty()) {
      expression_is_valid = false;
      return;
    }
    if (!operations.empty() && operations.top() == "(") {
      operations.pop();
    }
  } else if (input_operator == "(") {
    operations.push(Operation(input_operator));
  } else if (input_operator == "*") {
    while (!operations.empty() && Priority(input_operator) <= Priority(operations.top())) {
      rpn.push_back(new Operation(operations.top()));
      operations.pop();
    }
    operations.push(input_operator);
  } else if (input_operator == "-" || input_operator == "+") {
    while (!operations.empty() && Priority(input_operator) <= Priority(operations.top())) {
      rpn.push_back(new Operation(operations.top()));
      operations.pop();
    }
    operations.push(input_operator);
  }
}

void Worker::Calculate() {
  if (rpn.size() == 1 && rpn[0]->isOperation() == false) {
    result = *rpn[0];
    return;
  }
  std::stack<Integer*> calc;
  for (size_t i = 0; i < rpn.size(); ++i) {
    if (!rpn[i]->isOperation()) {
      calc.push(rpn[i]);
    } else {
      Integer* num1 = calc.top();
      calc.pop();
      if (rpn[i]->GetValue() == "*")
        *calc.top() *= *num1;
      else if (rpn[i]->GetValue() == "+")
        *calc.top() += *num1;
      else if (rpn[i]->GetValue() == "-")
        *calc.top() -= *num1;
    }
  }
  result = *calc.top();
  if (IsOverflow(result)) {
    overflow = true;
    result = Integer("Overflow");
  }
  calc.pop();
}

void Worker::ParseExpression() {
  bool first_symbol = true;
  bool prev_is_operation = true;
  size_t i = 0;

  while (i < expression.size() && expression_is_valid) {
    while (i < expression.size() && expression[i] == ' ') {
      ++i;
    }

    // check the first symbol in expression
    if (i < expression.size() && first_symbol) {
      if ((expression[i] != '-' && expression[i] != '(') && (expression[i] < '0' || expression[i] > '9')) {
        expression_is_valid = false;
        break;
      } else if (expression[i] == '-') {
        rpn.push_back(new Integer("0"));
        prev_is_operation = false;
        first_symbol = false;
      } else {
        first_symbol = false;
      }
    }

    // check if operation is valid
    if (i < expression.size() - 1 && !prev_is_operation &&
        (expression[i] == '+' || expression[i] == '-' || expression[i] == '*')) {
      prev_is_operation = true;
      ProcessOperationStack(Operation(expression[i]));
      ++i;
    } else if (i < expression.size() - 1 && prev_is_operation &&
               (expression[i] == '+' || expression[i] == '-' || expression[i] == '*')) {
      expression_is_valid = false;
      break;
    }

    // chek the last symbol
    if (i == expression.size() - 1 &&
        ((expression[i] < '0' || expression[i] > '9') && expression[i] != ')')) {
      expression_is_valid = false;
      break;
    }

    if (expression[i] == '(' || expression[i] == ')') {
      ProcessOperationStack(Operation(expression[i]));
      if (expression_is_valid == false) {
        break;
      }
      ++i;
    }

    std::string tmp_num;
    while (i < expression.size() && expression[i] >= '0' && expression[i] <= '9') {
      tmp_num += expression[i];
      ++i;
    }

    if (IsOverflow(tmp_num)) {
      overflow = true;
      break;
    }

    if (tmp_num.size() > 0 && prev_is_operation) {
      rpn.push_back(new Integer(tmp_num));
      prev_is_operation = false;
      tmp_num = "";
    } else if (tmp_num.size() > 0 && !prev_is_operation) {
      expression_is_valid = false;
      break;
    }
  }

  while (!operations.empty()) {
    if (operations.top().GetValue() == "(" || operations.top().GetValue() == ")") {
      expression_is_valid = false;
      break;
    }
    rpn.push_back(new Operation(operations.top()));
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

void Worker::CalcExpression(std::list<Integer>::iterator output_result) {
  ParseExpression();
  *output_result = result;
}

std::string Worker::GetRPN() {
  std:: string output_rpn;
  for (size_t i = 0; i < rpn.size(); ++i) {
    output_rpn += rpn[i]->GetValue();
    output_rpn += " ";
  }
  return output_rpn;
}
