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
  if (elem.IsImp()) {
    SetRedBlink();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefault();
  printf(" {");
  LogValue(elem);
  printf("} ");
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogValueCtor(const LogInt& elem) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlink();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefault();
  printf("(%d) ", elem.value_);
  printf("{");
  LogValue(elem);
  printf("} ");
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  LogShift();
  if (dst.IsImp()) {
    SetRedBlink();
  }
  printf("(New) ");
  printf("%s", dst.GetName().c_str());
  SetDefault();
  printf("(%s) ", src.GetName().c_str());
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
  printf("%s = %s ", dst.GetName().c_str(), src.GetName().c_str());
  printf("{");
  LogValue(dst);
  printf("} ");
  LogElem(dst);
  printf(" ");
  LogElem(src);
  printf("\n");
}

void ConLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlink();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefault();
  printf(" = %s%s ", op.c_str(), parent.GetName().c_str());
  printf("{");
  LogValue(elem);
  printf("} ");
  LogElem(elem);
  printf(" ");
  LogElem(parent);
  printf("\n");
}

void ConLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) {
  LogShift();
  if (elem.IsImp()) {
    SetRedBlink();
  }
  printf("(New) ");
  printf("%s", elem.GetName().c_str());
  SetDefault();
  printf(" = %s %s %s ", parent1.GetName().c_str(), op.c_str(), parent2.GetName().c_str());
  printf("{");
  LogValue(elem);
  printf("} ");
  LogElem(elem);
  printf(" ");
  LogElem(parent1);
  printf(" ");
  LogElem(parent2);
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
