#include "InputParser.hpp"
#include "string"

template <typename T>
class Calculator {
 public:
  static T CalculateExpr(const std::string& expr) {
    ExprInInfixToPolishNotation<T> parser(expr);
    std::vector<AbstractToken*>& tokens = parser.GetTokens();
    std::stack<T> operand_stack;
    for (AbstractToken* token : tokens) {
      if (auto operand_token = dynamic_cast<OperandToken<T>*>(token)) {
        operand_stack.push(operand_token->GetValue());

      } else if (auto* operator_token =
                     dynamic_cast<OperatorToken<T>*>(token)) {
        T op2 = operand_stack.top();
        operand_stack.pop();
        T op1 = operand_stack.top();
        operand_stack.pop();
        operand_stack.push(operator_token->Calculate(op1, op2));
      }
    }

    T result = operand_stack.top();
    operand_stack.pop();

    for (auto* token : tokens) {
      delete token;
    }

    tokens.clear();

    return result;
  }
};