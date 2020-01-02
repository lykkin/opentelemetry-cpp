#ifndef INCLUDE_OPEN_TELEMETRY_TRACE_TRACER_H_
#define INCLUDE_OPEN_TELEMETRY_TRACE_TRACER_H_
#include <string>
#include "./span.h"

namespace opentelemetry {
namespace trace {
class Span;
class Tracer {
 public:
  Tracer();
  Span* get_current_span() const;
  void set_current_span(Span*);
  Span* start_span(const std::string&);
  void on_span_end(const Span* const);

 private:
  Span* current_span;
  // Sampler sampler;
};
}  // namespace trace
}  // namespace opentelemetry
#endif  // INCLUDE_OPEN_TELEMETRY_TRACE_TRACER_H_
