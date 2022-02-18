#include "log_int.hpp"

size_t LogInt::exp_num_ = 0;
size_t LogInt::imp_num_ = 0;

LogInt::LogInt(const std::string& name) {
  SetName(name);
  ILogger::curr_logger_->LogDefaultCtor(*this);
}

LogInt::LogInt(const int value, const std::string& name): value_(value) {
  SetName(name);
  ILogger::curr_logger_->LogValueCtor(*this);
}

LogInt::LogInt(const LogInt& other, const std::string& name): value_(other.value_) {
  SetName(name);
  ILogger::curr_logger_->LogCopyCtor(*this, other);
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
  ILogger::curr_logger_->LogAssOp(*this, other);
  return *this;
}

#define UNARY_OPTOR(op) \
LogInt LogInt::operator op() const { \
  return LogInt(*this, op value_, #op); \
}

#define BINARY_OPTOR(op) \
LogInt LogInt::operator op(const LogInt& other) const { \
  return LogInt(*this, other, this->value_ op other.value_, #op); \
}

#define BINARY_ASS_OPTOR(op) \
LogInt& LogInt::operator op(const LogInt& other) { \
  value_ op other.value_; \
  ILogger::curr_logger_->LogBinaryAssOptor(*this, other, #op); \
  return *this; \
}

#define BINARY_COMP_OPTOR(op) \
bool LogInt::operator op(const LogInt& other) const { \
  ILogger::curr_logger_->LogCompOptor(*this, other, #op, value_ op other.value_); \
  return value_ op other.value_; \
}

#include "optors.hpp"

#undef BINARY_OPTOR
#undef UNARY_OPTOR
#undef BINARY_ASS_OPTOR
#undef BINARY_COMP_OPTOR

LogInt::LogInt(const LogInt& parent, const int value, const std::string& op): value_(value) {
  SetName();
  ILogger::curr_logger_->LogUnaryOptor(*this, parent, op);
}

LogInt::LogInt(const LogInt& parent1, const LogInt& parent2, const int value, const std::string& op): value_(value) {
  SetName();
  ILogger::curr_logger_->LogBinaryOptor(*this, parent1, parent2, op);
}

void LogInt::SetName(const std::string& name) {
  if (name != "") {
    ++exp_num_;
    is_imp_ = false;
    name_ = name + "#" + std::to_string(exp_num_);
  } else {
    ++imp_num_;
    is_imp_ = true;
    name_ = "IMP#" + std::to_string(imp_num_);
  }
}
