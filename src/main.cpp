#include "log_int.hpp"

void Func(const int*, size_t) {
  FUNC_CON_LOG_NL;
}

int main() {
  FUNC_CON_LOG_NL;

  LOG_INT_INIT_BY_COPY(a, LogInt(LogInt(1)));
  LogInt b = a;

  return 0;
}
