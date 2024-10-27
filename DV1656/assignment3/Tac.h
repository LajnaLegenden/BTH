#ifndef TAC_H
#define TAC_H

#include <string>
#include <iostream>

class Tac {
public:
  std::string op;
  std::string lhs;
  std::string rhs;
  std::string result;

  Tac() : op(""), lhs(""), rhs(""), result("") {}

  // Add constructor for creating TAC instructions
  Tac(const std::string& _op, const std::string& _lhs,
      const std::string& _rhs, const std::string& _result)
      : op(_op), lhs(_lhs), rhs(_rhs), result(_result) {}
};

class Expression : public Tac {
public:
  Expression(const std::string &_op, const std::string &_y, const std::string &_z, const std::string &_result) {
    op = _op;
    lhs = _y;
    rhs = _z;
    result = _result;
  }
};

class MethodCall : public Tac {
public:
  MethodCall(const std::string &_f, const std::string &_N, const std::string &_result) {
    op = "call";
    lhs = _f;
    rhs = _N;
    result = _result;
  }
};

class Jump : public Tac {
public:
  Jump(const std::string &_label) {
    op = "goto";
    result = _label;
  }
};

class CondJump : public Tac {
public:
  CondJump(const std::string &_op, const std::string &_x, const std::string &_label) {
    op = _op;
    lhs = _x;
    result = _label;
  }
};

#endif // TAC_H