#include <iostream>

#include "opentelemetry/trace/tracer.h"

namespace opentelemetry {
namespace trace {
Tracer::Tracer(): current_span(nullptr) {}
Span* Tracer::start_span(const std::string& name) {
  auto span = new Span(
    name,
    this,
    current_span ? current_span->get_context() : nullptr
  );
  current_span = span;
  return span;
}

Span* Tracer::get_current_span() const {
  return current_span;
}

void Tracer::set_current_span(Span* s) {
  current_span = s;
}

void Tracer::on_span_end(const Span* const span) {
  std::cout << "{" << std::endl;
  std::cout << "  \"name\": \"" << span->get_name()
    << "\"," << std::endl;
  std::cout << "  \"timestamp\": " << std::dec << span->get_start_time().count()
    << "," << std::endl;
  std::cout << "  \"duration\": " << std::dec << span->get_duration().count()
    << "," << std::endl;
  span->print_attributes();
  if (auto&& parent = span->get_parent_context()) {
    std::cout << "  \"parent_id\": \"";
    for (auto& c : parent->get_span_id()) {
      std::cout << std::hex << c;
    }
    std::cout << "\"," << std::endl;
  }
  std::cout << "  \"id\": \"";
  for (auto& c : span->get_context()->get_span_id()) {
    std::cout << std::hex << c;
  }
  std::cout << "\"," << std::endl;
  std::cout << "  \"trace_id\": \"";
  for (auto& c : span->get_context()->get_trace_id()) {
    std::cout << std::hex << c;
  }
  std::cout << "\"" << std::endl;
  std::cout << "}" << std::endl;
}
}  // namespace trace
}  // namespace opentelemetry
