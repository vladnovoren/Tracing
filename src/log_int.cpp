#include "log_int.hpp"

size_t LogInt::num_ = 0;

LogInt::LogInt(const char* name) {
  SetName(name);
  FUNC_CON_LOG_NL;
}

LogInt::LogInt(const int value, const char* name): value_(value) {
  SetName(name);
  FUNC_CON_LOG_NL;
}

LogInt::LogInt(const LogInt& other, const char* name): value_(other.value_) {
  SetName(name);
  FUNC_CON_LOG_NL;
}

LogInt::~LogInt() {
  FUNC_CON_LOG_NL;
}

LogInt& LogInt::operator=(const LogInt& other) {
  FUNC_CON_LOG_NL;
  value_ = other.value_;
  return *this;
}

void LogInt::SetName(const char* name) {
  name_ = name;
  if (name != nullptr) {
    is_tmp_var_ = true;
  } else {
    name_ = TMP_VAR;
  }
}
