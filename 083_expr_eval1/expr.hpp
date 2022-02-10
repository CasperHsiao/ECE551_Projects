#ifndef __EXPR_H__
#define __EXPR_H__
#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;

 public:
  explicit NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << number;
    return sstream.str();
  }
  virtual long evaluate() const { return number; }
};

class OpExpression : public Expression {
 protected:
  const char * op;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(const char * op, Expression * lhs, Expression * rhs) :
      op(op),
      lhs(lhs),
      rhs(rhs) {}
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << "(";
    sstream << lhs->toString();
    sstream << op;
    sstream << rhs->toString();
    sstream << ")";
    return sstream.str();
  }
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression(" + ", lhs, rhs) {}
  virtual long evaluate() const {
    long operandA = lhs->evaluate();
    long operandB = rhs->evaluate();
    return operandA + operandB;
  }
};
class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression(" - ", lhs, rhs) {}
  virtual long evaluate() const {
    long operandA = lhs->evaluate();
    long operandB = rhs->evaluate();
    return operandA - operandB;
  }
};
class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression(" * ", lhs, rhs) {}
  virtual long evaluate() const {
    long operandA = lhs->evaluate();
    long operandB = rhs->evaluate();
    return operandA * operandB;
  }
};
class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression(" / ", lhs, rhs) {}
  virtual long evaluate() const {
    long operandA = lhs->evaluate();
    long operandB = rhs->evaluate();
    return operandA / operandB;
  }
};

#endif
