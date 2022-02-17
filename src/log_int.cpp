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

#define UNARY_OPTOR(op) \
LogInt LogInt::operator op() const { \
  return LogInt(*this, op value_, #op); \
}

#define BINARY_OPTOR(op) \
LogInt LogInt::operator op(const LogInt& other) const { \
  return LogInt(*this, other, this->value_ op other.value_, #op); \
}

#define BINARY_ASS_OPTOR(op) \
LogInt LogInt::operator op(const LogInt& other) { \
  
}

#define BINARY_COMP_OPTOR(op) \
LogInt operator op(const LogInt& other) const;


#include "optors.hpp"

#undef BINARY_OPTOR
#undef UNARY_OPTOR

LogInt::LogInt(const LogInt& parent, const int value, const std::string& op): value_(value) {
  SetName();
  ConLogger::GetInstance().LogUnaryOptor(*this, parent, op);
}

LogInt::LogInt(const LogInt& parent1, const LogInt& parent2, const int value, const std::string& op): value_(value) {
  SetName();
  ConLogger::GetInstance().LogBinaryOptor(*this, parent1, parent2, op);
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
