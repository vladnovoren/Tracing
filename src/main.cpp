#include "func_logger.hpp"
#include "con_logger.hpp"
#include "log_int.hpp"
#include "log_initer.hpp"
#include "html_logger.hpp"
#include "move_semantics.hpp"

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

template<typename T>
void MovingSetter(T&& obj) {
  FUNC_LOG;
  volatile typename std::remove_reference<T>::type dst = my_move(obj);
}

template<typename T>
void ForwardingSetter(T&& obj) {
  FUNC_LOG;
  volatile typename std::remove_reference<T>::type dst = my_forward<T>(obj);
}

template<typename T>
void Wrapper(T&& obj) {
  FUNC_LOG;
  ForwardingSetter(my_forward<T>(obj));
}

int main() {
  LogIniter::GetInstance(LogType::GV);
  FUNC_LOG;

  LOG_INT_INIT_BY_VALUE(a, 42);

  // Wrapper(a);
  Wrapper(my_move(a));

  return 0;
}
