#include "log_int.hpp"

size_t LogInt::exp_num_ = 0;
size_t LogInt::imp_num_ = 0;

LogInt::LogInt(const std::string& name) {
  SetName(name);
  ConLogger::GetInstance().LogDefaultCtor(*this);
}

LogInt::LogInt(const int value, const std::string& name): value_(value) {
  SetName(name);
  ConLogger::GetInstance().LogValueCtor(*this);
}

LogInt::LogInt(const LogInt& other, const std::string& name): value_(other.value_) {
  SetName(name);
  ConLogger::GetInstance().LogCopyCtor(*this, other);
}

LogInt::~LogInt() {
}

const std::string& LogInt::GetName() const {
  return name_;
}

size_t LogInt::GetNum() const {
  return is_imp_ ? imp_num_ : exp_num_;
}

bool LogInt::IsImp() const {
  return is_imp_;
}

const char* LogInt::GetTypeStr() const {
  return is_imp_ ? IMP : EXP;
}

LogInt& LogInt::operator=(const LogInt& other) {
  value_ = other.value_;
  ConLogger::GetInstance().LogAssOp(*this, other);
  return *this;
}

#define UNARY_OPTOR(op, name) \
LogInt LogInt::operator op() const { \
  ConLogger::GetInstance().LogUnaryOptor(*this, #op, #name); \
  return LogInt(op value_, #op, #name); \
}

#include "optors.hpp"

#undef UNARY_OPTOR

LogInt::LogInt(const LogInt& parent, const int value, const std::string& op, const std::string& op_name): value_(value) {
  SetName();
  ConLogger::GetInstance().LogUnaryOptor(*this, op, op_name);
}

void LogInt::SetName(const std::string& name) {
  if (name != "") {
    ++exp_num_;
    is_imp_ = false;
    name_ = "\x1b[32m" + name + "#" + std::to_string(exp_num_) + "\x1b[0m";
  } else {
    ++imp_num_;
    is_imp_ = true;
    name_ = "\x1b[1;33mIMP#" + std::to_string(imp_num_) + "\x1b[0m";
  }
}
