#include <algorithm>
#include <random>

#include "opentelemetry/trace/span-context.h"

namespace opentelemetry {
namespace trace {
SpanContext::SpanContext(const SpanContext* const parent) {
  std::random_device rd;
  if (parent == nullptr) {
    trace_id = new TraceId();
    std::generate(trace_id->begin(), trace_id->end(), [&](){return rd();});
  } else {
    trace_id = parent->trace_id;
  }
  std::generate(span_id.begin(), span_id.end(), [&](){return rd();});
}

TraceId SpanContext::get_trace_id() const {
  return *trace_id;
}

SpanId SpanContext::get_span_id() const {
  return span_id;
}
}  // namespace trace
}  // namespace opentelemetry
