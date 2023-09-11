#include "RPN.h"

int precedence(char op) {
  if (op < 0)
    return 4;
  return op == '+' || op == '-'                ? 1
         : op == '*' || op == '/' || op == '%' ? 2
                                               : -1;
}

void process(stack<int> &s, char op) {
  if (op < 0) {
    int l = s.top();
    s.pop();
    switch (-op) {
    case '+':
      s.push(l);
      break;
    case '-':
      s.push(-l);
      break;
    }
  } else {
    int l = s.top();
    s.pop();
    int r = s.top();
    s.pop();
    switch (op) {
    case '+':
      s.push(l + r);
      break;
    case '-':
      s.push(l - r);
      break;
    case '*':
      s.push(l * r);
      break;
    case '/':
      s.push(l / r);
      break;
    case '%':
      s.push(l % r);
      break;
    }
  }
}

int calcExpression(const string &expression) {
  bool unaryPossible = true;
  stack<char> operators;
  stack<int> operands;
  for (size_t i = 0; i < expression.length(); i++) {
    debug(i, expression[i], operators, operands);
    if (expression[i] == ' ')
      continue;
    else if (expression[i] == '(')
      operators.push(expression[i]), unaryPossible = true;
    else if (expression[i] == ')') {
      while (operators.top() != '(') {
        process(operands, operators.top());
        operators.pop();
      }
      operators.pop();
      unaryPossible = false;
    } else if (expression[i] == '+' || expression[i] == '-' ||
               expression[i] == '*' || expression[i] == '/') {
      debug(i, expression[i], unaryPossible, operators, operands,
            precedence(expression[i]));
      char curop = expression[i];
      if (unaryPossible && (curop == '+' || curop == '-'))
        curop = -curop;
      while (!operators.empty() &&
             precedence(operators.top()) >= precedence(curop))
        process(operands, operators.top()), operators.pop();
      operators.push(curop);
      unaryPossible = true;
    } else {
      string operand;
      while (i < expression.size() && isalnum(expression[i]))
        operand += expression[i++];
      --i;
      debug(operand, i);
      if (isdigit(operand[0]))
        operands.push(atoi(operand.c_str()));
      else
        operands.push((operand[0] == '+' ? 1 : -1) *
                      atoi(operand.substr(1, operand.size() - 1).c_str()));
      unaryPossible = false;
      debug(operators, operands);
    }
  }
  while (!operators.empty()) {
    debug(operators.top(), precedence(operators.top()), operands);
    process(operands, operators.top());
    operators.pop();
  }
  return operands.top();
}