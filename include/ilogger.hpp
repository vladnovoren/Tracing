#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <cstdio>
#include <cassert>
#include <string>

class LogInt;

class ILogger {
 public:
  ILogger(const char* func);
  ~ILogger();

  static ILogger* curr_logger = nullptr;

  static size_t GetDepth();

  virtual void LogDefaultCtor(const LogInt& elem) = 0;
  virtual void LogValueCtor(const LogInt& elem) = 0;
  virtual void LogCopyCtor(const LogInt& dst, const LogInt& src) = 0;

  virtual void LogAssOp(const LogInt& dst, const LogInt& src) = 0;

  virtual void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) = 0;
  virtual void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) = 0;
  virtual void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) = 0;
  virtual void LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res) = 0;

  virtual void LogFuncEntry(const std::string& func);
  virtual void LogFuncEnd();

 private:
  ILogger() = default;

  virtual void LogShift() = 0;
  virtual void LogElem(const LogInt& elem) = 0;
  virtual void LogValue(const LogInt& elem) = 0;

  virtual void SetDefault() = 0;
  virtual void SetRedBlink() = 0;
  virtual void SetGreen() = 0;
  virtual void SetYellowBold() = 0;

  static size_t depth_;
  bool is_for_func_ = false;
};

#define FUNC_CON_LOG ILogger logger(__PRETTY_FUNCTION__)

#define FUNC_CON_LOG_NL \
  ILogger logger(__PRETTY_FUNCTION__); \
  printf("\n");

void SetDefault();
void SetRedBlink();
void SetGreen();
void SetYellowBold();

#endif /* logger.hpp */
