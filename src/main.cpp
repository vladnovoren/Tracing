#include "log_int.hpp"

void Func(const int*, size_t) {
  FUNC_CON_LOG_NL;
}

int main() {
  FUNC_CON_LOG_NL;

  LogInt c;
  LOG_INT_INIT_BY_COPY(a, LogInt(LogInt(1)));
  LOG_INT_INIT_BY_COPY(b, a);
  b = a;

  return 0;
}
