#ifndef FUNC_LOGGER_HPP
#define FUNC_LOGGER_HPP

#include "ilogger.hpp"

class FuncLogger {
 public:
  FuncLogger(const std::string& func) {
    ILogger::curr_logger->LogFuncEntry(func);
  }

  ~FuncLogger() {
    ILogger::curr_logger->LogFuncEnd();
  }
};

#endif /* func_logger.hpp */
