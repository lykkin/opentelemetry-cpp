#include <iostream>
#include "opentelemetry/trace/span.h"

std::chrono::milliseconds get_timestamp();
std::chrono::milliseconds get_timestamp() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  );
}

namespace opentelemetry {
namespace trace {
Span::Span(
  const std::string& name,
  Tracer* const t,
  const SpanContext* const parent
) :
  tracer(t),
  name(name),
  context(new SpanContext(parent)),
  parent_context(parent),
  start_time(get_timestamp()),
  end_time(0)
{}

Span::Span(const std::string& name, Tracer* const t) : Span(name, t, nullptr) {}

void Span::set_name(std::string n) {
  name = n;
}

std::string Span::get_name() const {
  return name;
}

std::chrono::milliseconds Span::get_duration() const {
  return end_time - start_time;
}

std::chrono::milliseconds Span::get_start_time() const {
  return start_time;
}

std::chrono::milliseconds Span::get_end_time() const {
  return end_time;
}

void Span::end() {
  end(get_timestamp());
}

void Span::end(std::chrono::milliseconds e) {
  end_time = e;
  tracer->on_span_end(this);
}

bool Span::is_ended() const {
  return end_time != std::chrono::milliseconds(0);
}

void Span::print_attributes() const {
  if (attributes.size() > 0) {
    std::cout << "  \"attributes\": {" << std::endl;
    for (auto&& [ key, att ] : attributes) {
      if (std::holds_alternative<std::unique_ptr<const std::string>>(att)) {
        auto v = *std::get<std::unique_ptr<const std::string>>(att).get();
        std::cout << "    " << key << ": \"" << v << "\"," << std::endl;
      } else if (std::holds_alternative<std::unique_ptr<const double>>(att)) {
        auto v = *std::get<std::unique_ptr<const double>>(att).get();
        std::cout << "    " << key << ": " << v << "," << std::endl;
      } else if (std::holds_alternative<std::unique_ptr<const bool>>(att)) {
        auto v = *std::get<std::unique_ptr<const bool>>(att).get();
        std::cout << "    " << key << ": " << v << "," << std::endl;
      } else if (std::holds_alternative<std::unique_ptr<const int64_t>>(att)) {
        auto v = *std::get<std::unique_ptr<const int64_t>>(att).get();
        std::cout << "    " << key << ": " << v << "," << std::endl;
      }
    }
    std::cout << "  }," << std::endl;
  }
}

template<>
void Span::add_attribute<double>(const std::string& k, const double v) {
  attributes[k] = std::make_unique<const double>(v);
}

template<>
void Span::add_attribute<std::string>(const std::string& k, std::string v) {
  attributes[k] = std::make_unique<const std::string>(v);
}

template<>
void Span::add_attribute<bool>(const std::string& k, const bool v) {
  attributes[k] = std::make_unique<const bool>(v);
}

template<>
void Span::add_attribute<int64_t>(const std::string& k, const int64_t v) {
  attributes[k] = std::make_unique<const int64_t>(v);
}

template<>
double Span::get_attribute<double>(const std::string& k) const {
  return *std::get<std::unique_ptr<const double>>(attributes.at(k)).get();
}

template<>
std::string Span::get_attribute<std::string>(const std::string& k) const {
  return *std::get<std::unique_ptr<const std::string>>(attributes.at(k)).get();
}

template<>
bool Span::get_attribute<bool>(const std::string& k) const {
  return *std::get<std::unique_ptr<const bool>>(attributes.at(k)).get();
}

template<>
int64_t Span::get_attribute<int64_t>(const std::string& k) const {
  return *std::get<std::unique_ptr<const int64_t>>(attributes.at(k)).get();
}

const SpanContext* Span::get_context() const {
  return context;
}

const SpanContext* Span::get_parent_context() const {
  return parent_context;
}
}  // namespace trace
}  // namespace opentelemetry
