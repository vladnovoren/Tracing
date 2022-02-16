#ifndef LOG_INT_HPP
#define LOG_INT_HPP

#include "con_logger.hpp"
#include <string>

static const char* const EXP = "EXP";
static const char* const IMP = "IMP";

class LogInt {
 public:
  LogInt(const std::string& name = "");
  LogInt(const int value, const std::string& name = "");
  LogInt(const LogInt& other, const std::string& name = "");
  ~LogInt();

  const std::string& GetName() const;
  size_t GetNum() const;
  bool IsImp() const;
  const char* GetTypeStr() const;

  LogInt& operator=(const LogInt& other);

  int value_ = 0;

  #define UNARY_OPTOR(op, name, disp) \
  LogInt operator op() const { \
    value_ = op value_; \
    ConLogger::GetInstance().LogUnaryOptor(#name, #disp, *this); \
    return *this; \
  }

  

 private:
  void SetName(const std::string& name);
  void LogName();

  std::string name_ = "";
  static size_t exp_num_;
  static size_t imp_num_;

  bool is_imp_ = true;
};

#define LOG_INT_DECL(var) LogInt var(#var)

#define LOG_INT_INIT_BY_INT(var, value) var()

#define LOG_INT_INIT_BY_COPY(var, other) LogInt var(other, #var)


// #define 

#endif /* log_int.hpp */
