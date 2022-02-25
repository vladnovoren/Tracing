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
  LogIniter::GetInstance(LogType::GV);

  FUNC_LOG;

  LOG_INT_INIT_BY_COPY(res, Fib(5));

  LogInt a(5), b(5), c(5);
  a = a + b;


  return 0;
}
