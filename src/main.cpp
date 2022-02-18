#include "func_logger.hpp"
#include "con_logger.hpp"
#include "log_int.hpp"
#include "log_initer.hpp"

void Func(const int*, size_t) {
  FUNC_CON_LOG;
}

LogInt Rec(const size_t n) {
  FUNC_CON_LOG;
  if (n <= 1) {
    return 1;
  } else {
    return Rec(n - 1) + Rec(n - 1) / Rec(n - 2);
  }
}

int main() {
  LogIniter::GetInstance();

  FUNC_CON_LOG;

  LOG_INT_INIT_BY_COPY(res, Rec(5));

  return 0;
}
