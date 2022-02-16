cmake_minimum_required(VERSION 3.16.3)

project(Tracing)

set(TRACING_SOURCE src/con_logger.cpp
                   src/log_int.cpp)

add_executable(Tracing ${TRACING_SOURCE} src/main.cpp)
target_include_directories(Tracing PUBLIC include/)