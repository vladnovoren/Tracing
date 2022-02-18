#ifndef LOG_INT_HPP
#define LOG_INT_HPP

#include "ilogger.hpp"
#include "func_logger.hpp"
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

  #define UNARY_OPTOR(op) \
  LogInt operator op() const;

  #define BINARY_OPTOR(op) \
  LogInt operator op(const LogInt& other) const;

  #define BINARY_ASS_OPTOR(op) \
  LogInt& operator op(const LogInt& other);

  #define BINARY_COMP_OPTOR(op) \
  bool operator op(const LogInt& other) const;

  #include "optors.hpp"

  #undef UNARY_OPTOR
  #undef BINARY_OPTOR
  #undef BINARY_ASS_OPTOR
  #undef BINARY_COMP_OPTOR

 private:
  // for unary operators
  LogInt(const LogInt& parent, const int value, const std::string& op);
  // for binary operators
  LogInt(const LogInt& parent1, const LogInt& parent2, const int value, const std::string& op);

  void SetName(const std::string& name = "");
  void LogName();

  std::string name_ = "";
  static size_t exp_num_;
  static size_t imp_num_;

  bool is_imp_ = true;
};

#define LOG_INT_DECL(var) LogInt var(#var)

#define LOG_INT_INIT_BY_VALUE(var, value) LogInt var(value, #var)

#define LOG_INT_INIT_BY_COPY(var, other) LogInt var(other, #var)


// #define 

#endif /* log_int.hpp */
