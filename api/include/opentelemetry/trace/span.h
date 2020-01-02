#ifndef INCLUDE_OPEN_TELEMETRY_TRACE_SPAN_H_
#define INCLUDE_OPEN_TELEMETRY_TRACE_SPAN_H_
#include <variant>
#include <cstdint>
#include <map>
#include <memory>
#include <chrono>
#include <string>

#include "./span-context.h"
#include "./tracer.h"

namespace opentelemetry {
namespace trace {
class Tracer;
class Span {
 public:
  Span(const std::string&, Tracer* const, const SpanContext* const);
  Span(const std::string&, Tracer* const);
  void set_name(std::string);
  std::string get_name() const;
  void end();
  void end(std::chrono::milliseconds);
  void print_attributes() const;
  std::chrono::milliseconds get_duration() const;
  std::chrono::milliseconds get_start_time() const;
  std::chrono::milliseconds get_end_time() const;
  bool is_ended() const;
  template<typename T>
  void add_attribute(const std::string&, const T);
  template<typename T>
  T get_attribute(const std::string&) const;
  const SpanContext* get_context() const;
  const SpanContext* get_parent_context() const;

 private:
  Tracer* const tracer;
  std::string name;
  const SpanContext* context;
  const SpanContext* const parent_context;
  std::chrono::milliseconds start_time;
  std::chrono::milliseconds end_time;
  std::map<
    std::string,
   std::variant<
      std::unique_ptr<const std::string>,
      std::unique_ptr<const int64_t>,
      std::unique_ptr<const bool>,
      std::unique_ptr<const double>
    >
  > attributes;
};
}  // namespace trace
}  // namespace opentelemetry
#endif  // INCLUDE_OPEN_TELEMETRY_TRACE_SPAN_H_
