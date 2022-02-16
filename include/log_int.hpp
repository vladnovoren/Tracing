#ifndef LOG_INT_HPP
#define LOG_INT_HPP

#include "con_logger.hpp"

static const char* const TMP_VAR = "TMP_VAR";

class LogInt {
 public:
  LogInt(const char* name = nullptr);
  LogInt(const int value, const char* name = nullptr);
  LogInt(const LogInt& other, const char* name = nullptr);
  ~LogInt();

  LogInt& operator=(const LogInt& other);

  int value_ = 0;

 private:
  void SetName(const char* name);
  void LogName();

  const char* name_ = nullptr;
  static size_t num_;

  bool is_tmp_var_ = false;
};

#define LOG_INT_DECL(var) LogInt var(#var)

#define LOG_INT_INIT_BY_INT(var, value) var()

#define LOG_INT_INIT_BY_

// #define 

#endif /* log_int.hpp */
