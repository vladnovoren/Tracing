#include "func_logger.hpp"
#include "con_logger.hpp"
#include "log_int.hpp"
#include "log_initer.hpp"
#include "html_logger.hpp"

void Func(const int*, size_t) {
  FUNC_LOG;
}

LogInt Fib(const size_t n) {
  FUNC_LOG;
  if (n <= 1) {
    return 1;
  } else {
    return Fib(n - 1) + Fib(n - 2);
  }
}

int main() {
  LogIniter::GetInstance(LogType::HTML);

  FUNC_LOG;

  LOG_INT_INIT_BY_COPY(res, Fib(5));

  return 0;
}
