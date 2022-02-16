#include "con_logger.hpp"

size_t ConLogger::depth_ = 0;

ConLogger::ConLogger(const char* func) {
  assert(func != nullptr);

  LogShift();
  printf("%s {\n", func);
  ++depth_;
}

ConLogger::~ConLogger() {
  --depth_;
  LogShift();
  printf("}\n");
}

void ConLogger::LogShift() {
  for (size_t i = 0; i < depth_; ++i) {
    printf("  ");
  }
}
