#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <utility>
#include "../include/mybiginteger.h"
#include "../include/mathoperations.h"

namespace mycalc {

// OperationPlus' methods implementation

OperationPriority OperationPlus::getPriority() const {
  return OperationPriority::PLUS;
}

bool OperationPlus::apply(std::stack<BigInteger *> *rpn_stack) {
  BigInteger *num1 = rpn_stack->top();
  rpn_stack->pop();
  *rpn_stack->top() += *num1;
  return true;
}

// OperationMinus' methods implementation

OperationPriority OperationMinus::getPriority() const {
  return OperationPriority::MINUS;
}

bool OperationMinus::apply(std::stack<BigInteger *> *rpn_stack) {
  BigInteger *num1 = rpn_stack->top();
  rpn_stack->pop();
  *rpn_stack->top() -= *num1;
  return true;
}

// OperationMultiple' methods implementation

OperationPriority OperationMultiple::getPriority() const {
  return OperationPriority::MULTIPLY;
}

bool OperationMultiple::apply(std::stack<BigInteger *> *rpn_stack) {
  BigInteger *num1 = rpn_stack->top();
  rpn_stack->pop();
  *rpn_stack->top() *= *num1;
  return true;
}

// OperationParenth' methods implementation

OperationPriority OperationParenthOpen::getPriority() const {
  return OperationPriority::OPEN_PARENTHESIS;
}

bool OperationParenthOpen::apply(std::stack<BigInteger *> *) {
  return true;
}

// OperationParenth' methods implementation

OperationPriority OperationParenthClose::getPriority() const {
  return OperationPriority::CLOSE_PARENTHESIS;
}

bool OperationParenthClose::apply(std::stack<BigInteger *> *) {
  return true;
}

// fabric for creating operation

std::unique_ptr<IOperation> IOperation::create(const char &operation) {
  switch (operation) {
    case '+': {
      return std::make_unique<OperationPlus>();
    }
    case '-': {
      return std::make_unique<OperationMinus>();
    }
    case '*': {
      return std::make_unique<OperationMultiple>();
    }
    case '(': {
      return std::make_unique<OperationParenthOpen>();
    }
    case ')': {
      return std::make_unique<OperationParenthClose>();
    }
    default: {
      return nullptr;
    }
  }
}

}  // namespace mycalc
