#include "Tockens.hpp"
#include "iostream"
#include "stack"
#include "vector"

template <typename T>
class ExprInInfixToPolishNotation {
 public:
  explicit ExprInInfixToPolishNotation(const std::string& expr) {
    std::stack<AbstractToken*> operator_stack;
    std::vector<std::string> parsed_expression = ParseExpression(expr);
    for (std::string token : parsed_expression) {
      if (IsBinaryOperator(token)) {
        AbstractToken* abstract_token = CreateOperatorToken(token);
        OperatorToken<T>* p_token =
            dynamic_cast<OperatorToken<T>*>(abstract_token);
        if (p_token) {
          while (!operator_stack.empty()) {
            OperatorToken<T>* operator_token =
                dynamic_cast<OperatorToken<T>*>(operator_stack.top());
            if (operator_token &&
                GetPrecedence(operator_token->GetStringToken()) >=
                    GetPrecedence(p_token->GetStringToken())) {
              tokens_.push_back(operator_stack.top());
              operator_stack.pop();
              delete p_token;
              delete operator_token;
              delete abstract_token;
            } else {
              break;
            }
          }
        }
        operator_stack.push(abstract_token);
      } else if (token == "(") {
        AbstractToken* abstract_token = new BracketToken(token);
        operator_stack.push(abstract_token);
      } else if (token == ")") {
        while (operator_stack.top()->GetStringToken() != "(") {
          tokens_.push_back(operator_stack.top());
          operator_stack.pop();
        }
        operator_stack.pop();
      } else {
        tokens_.push_back(new OperandToken<T>(token));
      }
    }
    while (!operator_stack.empty()) {
      tokens_.push_back(operator_stack.top());
      operator_stack.pop();
    }
  }

  std::vector<std::string> ParseExpression(const std::string& exp) {
    std::string copy = exp;
    copy.erase(remove(copy.begin(), copy.end(), ' '), copy.end());
    std::vector<std::string> expected_numbers = GetAllNumbers(copy);
    std::vector<std::string> result;
    for (size_t i = 0; i < copy.length(); i++) {
      char character = copy[i];
      if (IsOperator(std::string(1, character))) {
        result.emplace_back(1, character);
        continue;
      }
      if (IsNumber(character)) {
        for (std::string expected_number : expected_numbers) {
          if (character == expected_number[0]) {
            for (size_t j = 0; j < expected_number.length(); j++) {
              if (copy[i + j] == expected_number[j]) {
                if (j == expected_number.length() - 1) {
                  if (!result.empty()) {
                    if (CheckPreviousNumber(result, expected_number)) {
                      continue;
                    }
                  }
                  result.push_back(expected_number);
                  i += j;
                  RemoveElement(expected_numbers, expected_number);
                  break;
                }
                continue;
              }
              break;
            }
          }
        }
      }
    }

    CheckForUnaryOperators(result);

    CheckExpression(result);
    return result;
  };

  bool CheckPreviousNumber(std::vector<std::string>& collection,
                           const std::string& compare_with) {
    return collection[collection.size() - 1] == compare_with;
  }

  void RemoveElement(std::vector<std::string>& vector,
                     const std::string& element_to_remove) {
    for (size_t i = 0; i < vector.size(); i++) {
      if (vector[i] == element_to_remove) {
        vector[i] = "";
        break;
      }
    }
  }

  void CheckForUnaryOperators(std::vector<std::string>& collection_to_check) {
    std::string last_element;

    for (size_t i = 0; i < collection_to_check.size(); i++) {
      if (IsBinaryOperator(last_element) &&
              IsBinaryOperator(collection_to_check[i]) ||
          last_element == "(" && IsBinaryOperator((collection_to_check[i]))) {
        std::string right_value =
            collection_to_check[i] + collection_to_check[i + 1];
        collection_to_check[i + 1] = right_value;
        collection_to_check[i] = " ";
      }

      last_element = collection_to_check[i];
    }

    collection_to_check.erase(std::remove(collection_to_check.begin(),
                                          collection_to_check.end(), " "),
                              collection_to_check.end());
  };

  bool IsBinaryOperator(std::string& to_check) {
    return to_check == "+" || to_check == "-" || to_check == "*" ||
           to_check == "/";
  }

  std::vector<std::string> GetAllNumbers(std::string string) {
    std::vector<std::string> result;
    std::vector<char> delimiters;

    for (char element : string) {
      if (IsNumber(element)) {
        continue;
      }

      delimiters.emplace_back(element);
    }

    sort(delimiters.begin(), delimiters.end());
    delimiters.erase(unique(delimiters.begin(), delimiters.end()),
                     delimiters.end());

    size_t pos = 0;
    std::string token;

    for (char character : delimiters) {
      std::replace(string.begin(), string.end(), character, ' ');
    }

    while ((pos = string.find(' ')) != std::string::npos) {
      token = string.substr(0, pos);
      result.push_back(token);
      string.erase(0, pos + 1);
    }

    result.push_back(string);

    return result;
  }

  [[nodiscard]] std::vector<AbstractToken*>& GetTokens() { return tokens_; }

  void CheckExpression(std::vector<std::string>& expr) {
    CheckBrackets(expr);
    CheckSigns(expr);
  }

  bool IsNumber(char element) {
    return element >= '0' and element <= '9' || element == '.';
  }

  void CheckBrackets(std::vector<std::string>& expr) {
    int opening_brackets_amount = 0;
    int closing_brackets_amount = 0;

    for (const std::string& token : expr) {
      if (token == "(") {
        opening_brackets_amount++;
      }

      if (token == ")") {
        closing_brackets_amount++;
      }
    }

    if (opening_brackets_amount != closing_brackets_amount) {
      throw InvalidExpr();
    }
  }

  void CheckSigns(std::vector<std::string>& expr) {
    int signs_amount = 0;
    int operators_amount = 0;

    for (std::string token : expr) {
      if (IsBinaryOperator(token)) {
        signs_amount++;
      }

      if (IsOperator(token)) {
        operators_amount++;
      }
    }

    int numbers_amount = expr.size() - operators_amount;

    if (numbers_amount - signs_amount != 1) {
      throw InvalidExpr();
    }
  }

  struct InvalidExpr : std::exception {
    [[nodiscard]] const char* what() const noexcept override {
      return "Invalid expression!";
    }
  };

  ~ExprInInfixToPolishNotation() {
    for (AbstractToken* token : tokens_) {
      delete token;
    }
    tokens_.clear();
  }

 private:
  std::vector<AbstractToken*> tokens_;

  bool IsOperator(const std::string& str) const {
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "(" ||
           str == ")";
  }

  AbstractToken* CreateOperatorToken(const std::string& str) const {
    if (str == "+") {
      return new PlusOperator<T>(str);
    }
    if (str == "-") {
      return new MinusOperator<T>(str);
    }
    if (str == "*") {
      return new MultiplyOperator<T>(str);
    }
    if (str == "/") {
      return new DivideOperator<T>(str);
    }

    return nullptr;
  }

  int GetPrecedence(const std::string& str) const {
    if (str == "+" || str == "-") {
      return 1;
    }
    if (str == "*" || str == "/") {
      return 2;
    }
    return 0;
  }
};
