#include "gv_logger.hpp"

GVLogger::GVLogger() {
  log_file_ = fopen("log.dot", "w");
  fprintf(log_file_, "digraph {\n");
}

GVLogger::~GVLogger() {
  fprintf(log_file_, "}\n");
  fclose(log_file_);
}

void GVLogger::LogDefaultCtor(const LogInt& elem) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">];\n", last_node_id_, GetElemColor(elem));
  node_match_[elem.GetNum()] = last_node_id_;
  ++last_node_id_;
}

void GVLogger::LogValueCtor(const LogInt& elem) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">];\n", last_node_id_, GetElemColor(elem));
  node_match_[elem.GetNum()] = last_node_id_;
  ++last_node_id_;
}

void GVLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(dst));
  node_match_[dst.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[src.GetNum()], last_node_id_);
  ++last_node_id_;
}

void GVLogger::LogAssOp(const LogInt& dst, const LogInt& src) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(dst));
  node_match_[dst.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[src.GetNum()], last_node_id_);
  ++last_node_id_;
}

// void GVLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) {
void GVLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) {
  if (node_match_.find(parent.GetNum()) == node_match_.end()) {
    LogElem(parent);
  }
  if (node_match_.find(elem.GetNum()) == node_match_.end()) {
    LogElem(elem);
  }
  size_t elem_node_num = node_match_[elem.GetNum()];
  size_t parent_node_num = node_match_[parent.GetNum()];
  size_t op_node_num = last_node_id_;
  LogOptorNode(op);

}

// void GVLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) {
void GVLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string&) {
  fprintf(log_file_, "%zu [label = <<table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(elem));
  node_match_[elem.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent1.GetNum()], last_node_id_);
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent2.GetNum()], last_node_id_);
  ++last_node_id_;
  fprintf(log_file_, ">]\n");
}

// void GVLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) {
void GVLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string&) {
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[other.GetNum()], node_match_[elem.GetNum()]);
}

void GVLogger::LogFuncEntry(const std::string&) {
  fprintf(log_file_, "subgraph cluster_%zu {\n", funcs_cnt_);
  ++funcs_cnt_;
}

void GVLogger::LogFuncEnd() {
  fprintf(log_file_, "}\n");
}

void GVLogger::LogNodesLink(const size_t src_node, const size_t dst_node) {
  fprintf(log_file_, "%zu -> %zu\n", src_node, dst_node);
}

// void GVLogger::LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res) {}
void GVLogger::LogCompOptor(const LogInt&, const LogInt&, const std::string&, bool) {}

void GVLogger::LogShift() {}

void GVLogger::LogElem(const LogInt& elem) {
  fprintf(log_file_, "%zu [lable = <<table border = \"1\" bgcolor = \"%s\">\n", node_match_[elem.GetNum()], GetElemColor(elem));
  LogElemName(elem);
  LogElemValue(elem);
  LogElemAddress(elem);
  fprintf(log_file_, ">]\n");
}

void GVLogger::LogCtorNode(const std::string& name) {
  fprintf(log_file_, "%zu [label = \"%s\" shape = \"diamond\"]", last_node_id_, name.c_str());
  ++last_node_id_;
}

void GVLogger::LogOptorNode(const std::string& name) {
  fprintf(log_file_, "%zu [label = \"%s\" shape = \"circle\"]", last_node_id_, name.c_str());
  ++last_node_id_;
}

void GVLogger::LogElemValue(const LogInt& elem) {
  fprintf(log_file_, "<tr><td>value</td><td>%d</td></tr>\n", elem.value_);
}

void GVLogger::LogElemName(const LogInt& elem) {
  fprintf(log_file_, "<tr><td>name</td><td>%s</td></tr>\n", elem.GetName().c_str());
}

void GVLogger::LogElemAddress(const LogInt& elem) {
  fprintf(log_file_, "<tr><td>address</td><td>%p</td></tr>", static_cast<const void*>(&elem));
}

const char* GVLogger::GetElemColor(const LogInt& elem) {
  return (elem.IsImp() && node_match_[elem.GetNum()] == last_node_id_) ? "red" : "green";
}
