#include "sstream"
#include "string"

class AbstractToken {
 public:
  AbstractToken(const std::string& string_token)
      : string_token_(string_token) {}

  virtual ~AbstractToken() = default;

  const std::string& GetStringToken() const { return string_token_; }

 private:
  std::string string_token_;
};

class BracketToken : public AbstractToken {
 public:
  BracketToken(const std::string& str) : AbstractToken(str) {}

  bool IsOpening() const { return this->GetStringToken() == "("; }
};

template <typename T>
class OperandToken : public AbstractToken {
 public:
  OperandToken(const std::string& string_token) : AbstractToken(string_token) {
    std::stringstream sstrream(string_token);
    sstrream >> value_;
  }

  OperandToken(const T& value)
      : AbstractToken(std::to_string(value)), value_(value) {}

  const T& GetValue() const { return value_; }

 private:
  T value_;
};

template <typename T>
class OperatorToken : public AbstractToken {
 public:
  OperatorToken(const std::string& str) : AbstractToken(str) {}

  virtual bool IsBinary() const = 0;
  virtual T Calculate(const T& lhs, const T& rhs) const = 0;
  virtual T Calculate(const T& operand) const {
    if (this->IsBinary()) {
      throw std::logic_error(
          "Calculate(const T& operand) should not be called for binary "
          "operators");
    }

    return operand;
  }
};

template <typename T>
class NegateOperator : public OperatorToken<T> {
 public:
  NegateOperator(const std::string& str) : OperatorToken<T>(str) {}

  bool IsBinary() const override { return false; }
  T Calculate(const T& lhs, const T& rhs) const override {
    if (!this->IsBinary()) {
      throw std::logic_error(
          "Calculate(const T& lhs, const T& rhs) should not be called for not"
          "binary operators");
    }

    return lhs - rhs;
  }
  T Calculate(const T& operand) const override { return -operand; }
};

template <typename T>
class PlusOperator : public OperatorToken<T> {
 public:
  PlusOperator(const std::string& str) : OperatorToken<T>(str) {}

  bool IsBinary() const override { return true; }
  T Calculate(const T& lhs, const T& rhs) const override { return lhs + rhs; }
  T Calculate(const T& operand) const override {
    if (this->IsBinary()) {
      throw std::logic_error(
          "Calculate(const T& operand) should not be called for binary"
          "operators");
    }

    return operand;
  }
};

template <typename T>
class MinusOperator : public OperatorToken<T> {
 public:
  MinusOperator(const std::string& str) : OperatorToken<T>(str) {}

  bool IsBinary() const override { return true; }
  T Calculate(const T& lhs, const T& rhs) const override { return lhs - rhs; }

  T Calculate(const T& operand) const override {
    if (this->IsBinary()) {
      throw std::logic_error(
          "Calculate(const T& operand) should not be called for binary"
          "operators");
    }
    return operand;
  }
};

template <typename T>
class DivideOperator : public OperatorToken<T> {
 public:
  DivideOperator(const std::string& str) : OperatorToken<T>(str) {}

  bool IsBinary() const override { return true; }
  T Calculate(const T& lhs, const T& rhs) const override { return lhs / rhs; }
  T Calculate(const T& operand) const override {
    if (this->IsBinary()) {
      throw std::logic_error(
          "Calculate(const T& operand) should not be called for binary"
          "operators");
    }
    return operand;
  }
};

template <typename T>
class MultiplyOperator : public OperatorToken<T> {
 public:
  MultiplyOperator(const std::string& str) : OperatorToken<T>(str) {}

  bool IsBinary() const override { return true; }
  T Calculate(const T& lhs, const T& rhs) const override { return lhs * rhs; }
  T Calculate(const T& operand) const override {
    if (this->IsBinary()) {
      throw std::logic_error(
          "Calculate(const T& operand) should not be called for binary"
          "operators");
    }
    return operand;
  }
};