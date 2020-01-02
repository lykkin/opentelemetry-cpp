#include "opentelemetry/trace/tracer.h"

#include <gtest/gtest.h>

using opentelemetry::trace::Tracer;

TEST(Tracer, Constructor){
  auto t = new Tracer();
  ASSERT_EQ(t->get_current_span(), nullptr);
}

TEST(Tracer, StartSpan){
  auto t = new Tracer();
  auto s = t->start_span("test span");
  ASSERT_EQ(s->get_name(), "test span");
  ASSERT_EQ(s->get_parent_context(), nullptr);
  ASSERT_EQ(t->get_current_span(), s);
  auto child = t->start_span("child");
  ASSERT_EQ(t->get_current_span(), child);
  ASSERT_EQ(child->get_parent_context(), s->get_context());
}

TEST(Tracer, SetCurrentSpan){
  auto t = new Tracer();
  auto s = t->start_span("test span");
  auto child = t->start_span("child");
  ASSERT_EQ(t->get_current_span(), child);
  ASSERT_EQ(child->get_parent_context(), s->get_context());
  t->set_current_span(s);
  ASSERT_EQ(t->get_current_span(), s);
}
