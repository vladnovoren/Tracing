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
void GVLogger::LogUnaryOptor(const LogInt& elem, const LogInt& parent, const std::string&) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(elem));
  node_match_[elem.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent.GetNum()], last_node_id_);
  ++last_node_id_;
}

// void GVLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string& op) {
void GVLogger::LogBinaryOptor(const LogInt& elem, const LogInt& parent1, const LogInt& parent2, const std::string&) {
  fprintf(log_file_, "%zu [label = <table border = \"1\" bgcolor = \"%s\">\n];", last_node_id_, GetElemColor(elem));
  node_match_[elem.GetNum()] = last_node_id_;
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent1.GetNum()], last_node_id_);
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[parent2.GetNum()], last_node_id_);
  ++last_node_id_;
}

// void GVLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string& op) {
void GVLogger::LogBinaryAssOptor(const LogInt& elem, const LogInt& other, const std::string&) {
  fprintf(log_file_, "%zu -> %zu;\n", node_match_[other.GetNum()], node_match_[elem.GetNum()]);
}

void GVLogger::LogFuncEntry(const std::string& func) {
  fprintf(log_file_, "subgraph cluster_%s%zu {\n", func.c_str(), funcs_cnt_);
  ++funcs_cnt_;
}

void GVLogger::LogFuncEnd() {
  fprintf(log_file_, "}\n");
}

// void GVLogger::LogCompOptor(const LogInt& elem, const LogInt& other, const std::string& op, bool res) {}
void GVLogger::LogCompOptor(const LogInt&, const LogInt&, const std::string&, bool) {}

void GVLogger::LogShift() {}
void GVLogger::LogElem(const LogInt&) {}
void GVLogger::LogValue(const LogInt&) {}

const char* GVLogger::GetElemColor(const LogInt& elem) {
  return elem.IsImp() ? "red" : "green";
}