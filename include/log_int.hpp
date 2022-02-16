#ifndef LOG_INT_HPP
#define LOG_INT_HPP

#include "con_logger.hpp"

static const char* const EXP = "EXP";
static const char* const IMP = "IMP";

class LogInt {
 public:
  LogInt(const char* name = nullptr);
  LogInt(const int value, const char* name = nullptr);
  LogInt(const LogInt& other, const char* name = nullptr);
  ~LogInt();

  const char* GetName() const;
  size_t GetNum() const;
  bool IsImp() const;
  const char* GetTypeStr() const;

  LogInt& operator=(const LogInt& other);

  int value_ = 0;

 private:
  void SetName(const char* name);
  void LogName();

  const char* name_ = nullptr;
  static size_t exp_num_;
  static size_t imp_num_;

  bool is_imp_ = true;
};

#define LOG_INT_DECL(var) LogInt var(#var)

#define LOG_INT_INIT_BY_INT(var, value) var()

#define LOG_INT_INIT_BY_COPY(var, other) LogInt var(other, #var)


// #define 

#endif /* log_int.hpp */
