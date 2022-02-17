#include "log_int.hpp"

void Func(const int*, size_t) {
  FUNC_CON_LOG_NL;
}

LogInt Rec(const size_t n) {
  FUNC_CON_LOG_NL
  if (n <= 1) {
    return 1;
  } else {
    return Rec(n - 1) + Rec(n - 1) / Rec(n - 2);
  }
}

int main() {
  FUNC_CON_LOG_NL;

  LOG_INT_INIT_BY_COPY(res, Rec(5));

  // LOG_INT_DECL(c);
  // LOG_INT_INIT_BY_COPY(a, LogInt(LogInt(1)));
  // LOG_INT_INIT_BY_COPY(b, a);
  // LOG_INT_INIT_BY_COPY(d, a * b + b * c);



  return 0;
}
