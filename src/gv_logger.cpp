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
  size_t elem_id = LogConnectPrevOccurrence(elem);
  size_t ctor_node_id = LogCtorNode("DefaultCtor");
  LogElem(elem);
  fprintf(log_file_, "%zu -> %zu;\n", ctor_node_id, node_match_[elem.GetNum()]);
}

void GVLogger::LogValueCtor(const LogInt& elem) {
  size_t elem_id = LogConnectPrevOccurrence(elem);
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">];\n", elem_id, GetElemColor(elem));
}

void GVLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {

  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">\n];", , GetElemColor(dst));
  fprintf(log_file_, "%zu -> %zu;\n", , );
  ++last_node_id_;
}

void GVLogger::LogAssOp(const LogInt& dst, const LogInt& src) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(dst));
  node_match_[dst.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[src.GetNum()], last_node_id_);
  ++last_node_id_;
}

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

void GVLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string&) {
  fprintf(log_file_, "%zu [label = <<table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(elem));
  node_match_[elem.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent1.GetNum()], last_node_id_);
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent2.GetNum()], last_node_id_);
  ++last_node_id_;
  fprintf(log_file_, ">]\n");
}

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

size_t GVLogger::FetchAddId() {
  size_t prev = last_node_id_;
  ++last_node_id_;
  return prev;
}

void GVLogger::LogNodesLink(const size_t src_node, const size_t dst_node) {
  fprintf(log_file_, "%zu -> %zu\n", src_node, dst_node);
}

void GVLogger::LogCompOptor(const LogInt&, const LogInt&, const std::string&, bool) {}

void GVLogger::LogShift() {}

void GVLogger::LogElem(const LogInt& elem) {
  size_t node_id = LogConnectPrevOccurrence(elem);
  fprintf(log_file_, "%zu [lable = <<table border = \"1\" bgcolor = \"%s\">\n", node_id, GetElemColor(elem));
  LogElemName(elem);
  LogElemValue(elem);
  LogElemAddress(elem);
  fprintf(log_file_, ">];\n");
}

size_t GVLogger::LogCtorNode(const std::string& name) {
  size_t ctor_node_id = FetchAddId();
  fprintf(log_file_, "%zu [label = \"%s\" shape = \"diamond\"]", ctor_node_id, name.c_str());
  return ctor_node_id;
}

size_t GVLogger::LogOptorNode(const std::string& name) {
  size_t node_id = FetchAddId();
  fprintf(log_file_, "%zu [label = \"%s\" shape = \"circle\"]", node_id, name.c_str());
  return node_id;
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

size_t GVLogger::LogConnectPrevOccurrence(const LogInt& elem) {
  size_t last_id = 0;
  if (node_match_.find(elem.GetNum()) != node_match_.end()) {
    size_t prev_id = node_match_[elem.GetNum()];
    size_t curr_id = node_match_[elem.GetNum()] = FetchAddId();
    last_id = curr_id;
    fprintf(log_file_, "%zu -> %zu [style = dotted];\n", prev_id, curr_id);
  } else {
    last_id = node_match_[elem.GetNum()] = FetchAddId();
  }
  return last_id;
}

const char* GVLogger::GetElemColor(const LogInt& elem) {
  return elem.IsImp() ? "red" : "green";
}
