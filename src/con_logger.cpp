#include "con_logger.hpp"
#include "log_int.hpp"

size_t ConLogger::depth_ = 0;

ConLogger::ConLogger(const char* func) {
  assert(func != nullptr);

  is_for_func_ = true;
  LogShift();
  printf("%s {", func);
  ++depth_;
}

ConLogger::~ConLogger() {
  if (is_for_func_) {
    --depth_;
    LogShift();
    printf("}\n");
  }
}

ConLogger& ConLogger::GetInstance() {
  static ConLogger instance;
  return instance;
}

size_t ConLogger::GetDepth() {
  return depth_;
}

void ConLogger::LogDefaultCtor(const LogInt& elem) {
  LogShift();
  printf("%-12s", "DefaultCtor");
  printf("%s", elem.GetName().c_str());
  printf(" {");
  LogValue(elem);
  printf("} ");
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogValueCtor(const LogInt& elem) {
  LogShift();
  printf("%-12s", "ValueCtor");
  printf("%-20s", (elem.GetName() + "(" + std::to_string(elem.value_) + ")").c_str());
  printf("{");
  LogValue(elem);
  printf("} ");
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  LogShift();
  SetRedBlink();
  printf("%-12s", "CopyCtor");
  SetDefault();

  printf("%s", (dst.GetName() + "(" + src.GetName().c_str() + ") ").c_str());
  printf("{");
  LogValue(dst);
  printf("} ");
  LogElem(dst);
  printf(" ");
  LogElem(src);
  printf("\n");
}

void ConLogger::LogAssOp(const LogInt& dst, const LogInt& src) {
  LogShift();
  printf("%-12s", "AssOptor");
  printf("%s = %s ", dst.GetName().c_str(), src.GetName().c_str());
  printf("{");
  LogValue(dst);
  printf("} ");
  LogElem(dst);
  printf(" ");
  LogElem(src);
  printf("\n");
}

void ConLogger::LogShift() {
  for (size_t i = 0; i < depth_; ++i) {
    printf("  ");
  }
}

void ConLogger::LogElem(const LogInt& elem) {
  printf("%s[%p]", elem.GetName().c_str(), static_cast<const void*>(&elem));
}

void ConLogger::LogValue(const LogInt& elem) {
  printf("%s.value_ = %d", elem.GetName().c_str(), elem.value_);
}

void SetDefault() {
  printf("\x1b[0m");
}

void SetRedBlink() {
  printf("\x1b[5;33m");
}

void SetGreen() {
  printf("\x1b[32m");
}

void SetYellowBold() {
  printf("\x1b[1;33m");
}
