#ifndef LOG_INITER_HPP
#define LOG_INITER_HPP

#include "ilogger.hpp"
#include "con_logger.hpp"
#include "html_logger.hpp"

enum class LogType {
  CONSOLE,
  HTML
};

class LogIniter {
 public:
  static LogIniter& GetInstance(const LogType log_type = LogType::CONSOLE);

 protected:
  LogIniter(const LogType log_type);
  ~LogIniter();

  static void SwitchLogType(const LogType log_type);

  static LogType curr_type_;
};

#endif /* log_initer.hpp */
