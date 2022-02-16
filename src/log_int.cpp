#include "log_int.hpp"

size_t LogInt::exp_num_ = 0;
size_t LogInt::imp_num_ = 0;

LogInt::LogInt(const char* name) {
  SetName(name);
  ConLogger::GetInstance().LogDefaultCtor(*this);
}

LogInt::LogInt(const int value, const char* name): value_(value) {
  SetName(name);
  ConLogger::GetInstance().LogValueCtor(*this);
}

LogInt::LogInt(const LogInt& other, const char* name): value_(other.value_) {
  SetName(name);
  ConLogger::GetInstance().LogCopyCtor(*this, other);
}

LogInt::~LogInt() {
}

const char* LogInt::GetName() const {
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
  FUNC_CON_LOG_NL;
  value_ = other.value_;
  return *this;
}

void LogInt::SetName(const char* name) {
  name_ = name;
  if (name != nullptr) {
    is_imp_ = false;
    ++exp_num_;
  } else {
    is_imp_ = true;
    name_ = IMP;
    ++imp_num_;
  }
}
