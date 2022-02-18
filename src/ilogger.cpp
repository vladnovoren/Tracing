#include "ilogger.hpp"

ILogger* ILogger::curr_logger = nullptr;

size_t ILogger::GetDepth() {
  return depth_;
}
