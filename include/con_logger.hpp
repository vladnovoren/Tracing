#ifndef CON_LOGGER_HPP
#define CON_LOGGER_HPP

#include <cstdio>
#include <cassert>
#include <string>

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

  void LogAssOp(const LogInt& dst, const LogInt& src);

  void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op);
  void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op);
  void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op);
  void LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res);

 private:
  ConLogger() = default;

  void LogShift();
  void LogElem(const LogInt& elem);
  void LogValue(const LogInt& elem);

  static size_t depth_;
  bool is_for_func_ = false;
};

#define FUNC_CON_LOG ConLogger logger(__PRETTY_FUNCTION__)

#define FUNC_CON_LOG_NL \
  ConLogger logger(__PRETTY_FUNCTION__); \
  printf("\n");

void SetDefault();
void SetRedBlink();
void SetGreen();
void SetYellowBold();

#endif /* con_logger.hpp */
