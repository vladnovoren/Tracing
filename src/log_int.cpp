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
