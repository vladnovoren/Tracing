#ifndef CON_LOGGER_HPP
#define CON_LOGGER_HPP

#include <cstdio>
#include <cassert>
#include <string>
#include "ilogger.hpp"

class LogInt;

class ConLogger: public ILogger {
 public:
  ConLogger() = default;
  ~ConLogger();

  void LogDefaultCtor(const LogInt& elem) override;
  void LogValueCtor(const LogInt& elem) override;
  void LogCopyCtor(const LogInt& dst, const LogInt& src) override;

  void LogAssOp(const LogInt& dst, const LogInt& src) override;

  void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) override;
  void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) override;
  void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) override;
  void LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res) override;

 private:
  ConLogger() = default;

  void LogShift() override;
  void LogElem(const LogInt& elem) override;
  void LogValue(const LogInt& elem) override;

  virtual void SetDefault() = 0;
  virtual void SetRedBlink() = 0;
  virtual void SetGreen() = 0;
  virtual void SetYellowBold() = 0;

  static size_t depth_;
  bool is_for_func_ = false;
};

#endif /* con_logger.hpp */
