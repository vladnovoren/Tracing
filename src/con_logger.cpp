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
  LogNewVar();
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogValueCtor(const LogInt& elem) {
  LogShift();
  LogNewVar();
  LogElem(elem);
  printf(" <---(.value_ = %d)\n", elem.value_);
}

void ConLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  LogShift();
  LogNewVar();
  printf("\033[5;31mCOPY \033[0m");
  LogElem(dst);
  printf(" <---(.value_ = %d)--- ", dst.value_);
  LogElem(src);
  printf("\n");
}

void ConLogger::LogShift() {
  for (size_t i = 0; i < depth_; ++i) {
    printf("  ");
  }
}

void ConLogger::LogNewVar() {
  printf("new ");
}

void ConLogger::LogElem(const LogInt& elem) {
  printf("%s [", elem.GetTypeStr());
  if (!elem.IsImp()) {
    printf("%s | ", elem.GetName());
  }
  printf("#%zu | %p]", elem.GetNum(), static_cast<const void*>(&elem));
}
