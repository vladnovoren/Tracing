cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic

    -fno-elide-constructors

    -fsanitize=address
)

add_link_options(
    -fno-elide-constructors

    -fsanitize=address
)

project(Tracing)

set(TRACING_SOURCE src/con_logger.cpp
                   src/func_logger.cpp
                   src/ilogger.cpp
                   src/log_int.cpp
                   src/log_initer.cpp
                   src/html_logger.cpp)

add_executable(Tracing ${TRACING_SOURCE} src/main.cpp)
target_include_directories(Tracing PUBLIC include/)
