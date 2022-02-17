cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic

    -fno-elide-constructors
)

add_link_options(
    -fno-elide-constructors
)

project(Tracing)

set(TRACING_SOURCE src/con_logger.cpp
                   src/log_int.cpp)

add_executable(Tracing ${TRACING_SOURCE} src/main.cpp)
target_include_directories(Tracing PUBLIC include/)
