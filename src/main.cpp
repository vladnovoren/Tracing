#include "log_int.hpp"

void Func(const int* a, size_t b) {
  FUNC_CON_LOG_NL;
}

int main() {
  FUNC_CON_LOG_NL;
  Func(nullptr, 2);
  LogInt a(2);
  LogInt b(a);
  return 0;
}