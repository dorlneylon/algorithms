#include "RPN.h"

int precedence(char op) {
  if (op < 0)
    return 4;
  return op == '+' || op == '-'                ? 1
         : op == '*' || op == '/' || op == '%' ? 2
                                               : -1;
}

string infixToRPN(const string& expression) {
    stack<char> operators;
    string rpn;
    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
        continue;
        else if (expression[i] == '(')
            operators.push(expression[i]);
        else if (expression[i] == ')') {
            while (operators.top() != '(') {
                rpn += operators.top();
                operators.pop();
            }
            operators.pop();
        } else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/' ||
                 expression[i] == '%') {
            while (!operators.empty() && operators.top() != '(' &&
                    precedence(operators.top()) >= precedence(expression[i])) {
                rpn += operators.top();
                operators.pop();
            }
            operators.push(expression[i]);
        } else {
            while (i < expression.length() && isdigit(expression[i]))
                rpn += expression[i++];
            rpn += ' ';
            i--;
        }
    }
    while (!operators.empty()) {
        rpn += operators.top();
        operators.pop();
    }
    return rpn;
}

int calcExpression(const string& expression) {
    // use infixToRPN to convert expression to RPN
    // then calculate the result
    string rpn = infixToRPN(expression);
    stack<int> operands;
    for (size_t i = 0; i < expression.size(); ++i) {
        if (expression[i] == ' ') continue;
        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/' ||
                 expression[i] == '%') {
            int r = operands.top();
            operands.pop();
            int l = operands.top();
            operands.pop();
            switch (expression[i]) {
                case '+':
                    operands.push(l + r);
                    break;
                case '-':
                    operands.push(l - r);
                    break;
                case '*':
                    operands.push(l * r);
                    break;
                case '/':
                    operands.push(l / r);
                    break;
                case '%':
                    operands.push(l % r);
                    break;
            }
        } else {
            int num = 0;
            while (i < expression.size() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                ++i;
            }
            operands.push(num);
            --i;
        }
    }
}