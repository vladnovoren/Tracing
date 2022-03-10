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
  size_t elem_node_id = NewOccurrence(elem);
  LogElem(elem);

  size_t ctor_node_id = LogCtorNode("DefaultCtor");
  LogNodesLink(ctor_node_id, elem_node_id);
}

void GVLogger::LogValueCtor(const LogInt& elem) {
  size_t elem_node_id = NewOccurrence(elem);
  LogElem(elem);

  size_t ctor_node_id = LogCtorNode("ValueCtor");
  LogNodesLink(ctor_node_id, elem_node_id);
}

void GVLogger::LogCopyCtor(const LogInt& dst, const LogInt& src) {
  size_t dst_node_id = NewOccurrence(dst);
  LogElem(dst);

  size_t src_node_id = LastElemId(src);
  size_t ctor_node_id = LogCtorNode("CopyCtor");

  LogNodesLink(src_node_id, ctor_node_id);
  LogNodesLink(ctor_node_id, dst_node_id);
}

void GVLogger::LogAssOptor(const LogInt& dst, const LogInt& src) {
  size_t src_node_id = LastElemId(src);
  size_t dst_node_id = NewOccurrence(dst);
  LogElem(dst);

  size_t optor_node_id = LogOptorNode("CopyAssOptor");

  LogNodesLink(src_node_id, optor_node_id);
  LogNodesLink(optor_node_id, dst_node_id);
}

void GVLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string& op) {
  size_t parent_node_id = LastElemId(parent);
  size_t elem_node_id = NewOccurrence(elem);
  LogElem(elem);

  size_t optor_node_id = LogOptorNode(op);

  LogNodesLink(parent_node_id, optor_node_id);
  LogNodesLink(optor_node_id, elem_node_id);
}

void GVLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) {
  size_t parent1_node_id = NewOccurrence(parent1);
  size_t parent2_node_id = NewOccurrence(parent2);

  size_t elem_node_id = NewOccurrence(elem);
  LogElem(elem);

  size_t optor_node_id = LogOptorNode(op);

  LogNodesLink(parent1_node_id, optor_node_id);
  LogNodesLink(parent2_node_id, optor_node_id);
  LogNodesLink(optor_node_id, elem_node_id);
}

void GVLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) {
  size_t other_node_id = LastElemId(other);
  size_t elem_node_id = NewOccurrence(elem);

  size_t optor_node_id = LogOptorNode(op);

  LogNodesLink(other_node_id, optor_node_id);
  LogNodesLink(optor_node_id, elem_node_id);
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

void GVLogger::LogShift() {}

void GVLogger::LogElem(const LogInt& elem) {
  size_t node_id = LastElemId(elem);
  if (logged_[node_id]) {
    return;
  }
  logged_[node_id] = true;
  fprintf(log_file_, "%zu [shape = \"none\" label = <<table border = \"1\" bgcolor = \"%s\">\n", node_id, GetElemColor(elem));
  LogElemName(elem);
  LogElemValue(elem);
  LogElemAddress(elem);
  fprintf(log_file_, "</table>>]\n");
}

size_t GVLogger::LogCtorNode(const std::string& name) {
  size_t ctor_node_id = FetchAddId();
  fprintf(log_file_, "%zu [label = \"%s\" shape = \"diamond\"]\n", ctor_node_id, name.c_str());
  return ctor_node_id;
}

size_t GVLogger::LogOptorNode(const std::string& name) {
  size_t node_id = FetchAddId();
  fprintf(log_file_, "%zu [label = \"%s\" shape = \"circle\"]\n", node_id, name.c_str());
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

size_t GVLogger::NewOccurrence(const LogInt& elem) {
  size_t last_id = 0;
  if (node_match_.find(elem.GetNum()) != node_match_.end()) {
    size_t prev_id = node_match_[elem.GetNum()];
    size_t curr_id = node_match_[elem.GetNum()] = FetchAddId();
    last_id = curr_id;
    fprintf(log_file_, "%zu -> %zu [style = dotted]\n", prev_id, curr_id);
    LogElem(elem);
  } else {
    last_id = node_match_[elem.GetNum()] = FetchAddId();
  }
  return last_id;
}

size_t GVLogger::LastElemId(const LogInt& elem) {
  return node_match_[elem.GetNum()];
}

const char* GVLogger::GetElemColor(const LogInt& elem) {
  return elem.IsImp() ? "red" : "green";
}
