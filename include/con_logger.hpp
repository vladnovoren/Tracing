#ifndef CON_LOGGER_HPP
#define CON_LOGGER_HPP

#include <cstdio>
#include <cassert>

class ConLogger {
 public:
  ConLogger(const char* func);
  ~ConLogger();
 private:
  void LogShift();

  static size_t depth_;
};

#define FUNC_CON_LOG ConLogger con_logger(__PRETTY_FUNCTION__)

#define FUNC_CON_LOG_NL \
  ConLogger con_logger(__PRETTY_FUNCTION__); \
  printf("\n");

#endif /* con_logger.hpp */
