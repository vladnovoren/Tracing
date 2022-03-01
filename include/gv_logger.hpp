#ifndef GV_LOGGER_HPP
#define GV_LOGGER_HPP

#include <cstdlib>
#include <map>
#include "ilogger.hpp"
#include "log_int.hpp"

class GVLogger: public ILogger {
 public:
  GVLogger();
  ~GVLogger();

  void LogDefaultCtor(const LogInt& elem) override;
  void LogValueCtor(const LogInt& elem) override;
  void LogCopyCtor(const LogInt& dst, const LogInt& src) override;

  void LogAssOp(const LogInt& dst, const LogInt& src) override;

  void LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) override;
  void LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) override;
  void LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) override;
  void LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res) override;

  void LogFuncEntry(const std::string& func) override;
  void LogFuncEnd() override;

 protected:
  size_t FetchAddId();

  void LogNodesLink(const size_t src_node, const size_t dst_node);

  size_t LogOptorNode(const std::string& name);
  size_t LogCtorNode(const std::string& name);

  void LogShift() override;
  void LogElem(const LogInt& elem) override;
  void LogElemValue(const LogInt& elem) override;
  void LogElemName(const LogInt& elem);
  void LogElemAddress(const LogInt& elem);

  size_t LogConnectPrevOccurrence(const LogInt& elem);

  const char* GetElemColor(const LogInt& elem);

  FILE* log_file_ = nullptr;
  size_t funcs_cnt_ = 0;

  std::map<size_t, size_t> node_match_;
  size_t last_node_id_ = 0;
};

#endif /* gv_logger.hpp */
