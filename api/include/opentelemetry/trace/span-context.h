#ifndef INCLUDE_OPEN_TELEMETRY_TRACE_SPAN_CONTEXT_H_
#define INCLUDE_OPEN_TELEMETRY_TRACE_SPAN_CONTEXT_H_
#include <string>
#include <array>

namespace opentelemetry {
namespace trace {
typedef std::array<int, 16/sizeof(int)> TraceId;
typedef std::array<int, 8/sizeof(int)> SpanId;
// typedef TraceOptions struct {
//   bool recorded
// }
//
// typedef TraceState struct {
//   std::string state
// }

class SpanContext final {
 public:
  explicit SpanContext(const SpanContext* const);
  TraceId get_trace_id() const;
  SpanId get_span_id() const;
 private:
  TraceId* trace_id;
  SpanId span_id;
  // TraceOptions options;
  // TraceState* state;
  // bool is_valid;
};
}  // namespace trace
}  // namespace opentelemetry
#endif  // INCLUDE_OPEN_TELEMETRY_TRACE_SPAN_CONTEXT_H_
