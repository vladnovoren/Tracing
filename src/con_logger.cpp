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
  printf("DefaultCtor %s ", elem.GetName());
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogValueCtor(const LogInt& elem) {
  LogShift();
  printf("ValueCtor %s(%d) ", elem.GetName(), elem.value_);
  LogElem(elem);
  printf("\n");
}

void ConLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {

  LogShift();
  printf("\033[5;31mCopyCtor \033[0m");
  printf("%s ", dst.GetName());
  LogElem(dst);
  printf(" <---(.value_ = %d)--- ", dst.value_);
  printf("%s ", src.GetName());
  LogElem(src);
  printf("\n");
}

void ConLogger::LogShift() {
  for (size_t i = 0; i < depth_; ++i) {
    printf("  ");
  }
}

void ConLogger::LogElem(const LogInt& elem) {
  printf("[#%zu | this = %p]", elem.GetNum(), static_cast<const void*>(&elem));
}
