#include "log_initer.hpp"

LogType LogIniter::curr_type_ = LogType::CONSOLE;

LogIniter& LogIniter::GetInstance(const LogType log_type) {
  static LogIniter log_initer(log_type);
  SwitchLogType(log_type);
  return log_initer;
}

LogIniter::LogIniter(const LogType log_type) {
  switch (log_type) {
    case LogType::CONSOLE:
      ILogger::curr_logger_ = new ConLogger;
      break;
  }
}

LogIniter::~LogIniter() {
  delete ILogger::curr_logger_;
}

void LogIniter::SwitchLogType(const LogType log_type) {
  if (log_type != curr_type_) {
    delete ILogger::curr_logger_;
    switch (log_type) {
      case LogType::CONSOLE:
        ILogger::curr_logger_ = new ConLogger;
        break;
    }
  }
}
