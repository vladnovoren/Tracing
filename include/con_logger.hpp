#ifndef CON_LOGGER_HPP
#define CON_LOGGER_HPP

#include <cstdio>
#include <cassert>

class LogInt;

class ConLogger {
 public:
  ConLogger(const char* func);
  ~ConLogger();

  static ConLogger& GetInstance();
  static size_t GetDepth();

  void LogDefaultCtor(const LogInt& elem);
  void LogValueCtor(const LogInt& elem);
  void LogCopyCtor(const LogInt& dst, const LogInt& src);

 private:
  ConLogger() = default;

  void LogShift();
  void LogElem(const LogInt& elem);

  static size_t depth_;
  bool is_for_func_ = false;
};

#define FUNC_CON_LOG ConLogger logger(__PRETTY_FUNCTION__)

#define FUNC_CON_LOG_NL \
  ConLogger logger(__PRETTY_FUNCTION__); \
  printf("\n");

#endif /* con_logger.hpp */
