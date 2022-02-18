#ifndef HTML_LOGGER_HPP
#define HTML_LOGGER_HPP

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <string>
#include "ilogger.hpp"
#include "log_int.hpp"

class LogInt;

class HTMLLogger: public ILogger {
 public:
  HTMLLogger();
  ~HTMLLogger() override;

  void LogDefaultCtor(const LogInt& elem) override;
  void LogValueCtor(const LogInt& elem) override;
  void LogCopyCtor(const LogInt& dst, const LogInt& src) override;

  void LogAssOp(const LogInt& dst, const LogInt& src) override;

  void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) override;
  void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) override;
  void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) override;
  void LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res) override;

  void LogFuncEntry(const std::string& func) override;
  void LogFuncEnd() override;

 private:
  void LogShift() override;
  void LogElem(const LogInt& elem) override;
  void LogValue(const LogInt& elem) override;

  void SetDefault() override;
  void SetRedBlink() override;
  void SetGreen() override;
  void SetYellowBold() override;

  FILE* log_file_ = nullptr;

  bool is_blink_ = false;
  bool is_bold_  = false;
};

#endif /* html_logger.hpp */
