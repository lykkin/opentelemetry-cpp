#include "opentelemetry/trace/span.h"
#include "opentelemetry/trace/tracer.h"

#include <gtest/gtest.h>

using opentelemetry::trace::Span;
using opentelemetry::trace::Tracer;

TEST(Span, ConstructorNoParent){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  EXPECT_EQ(s->get_name(), "test name");
}

TEST(Span, DoubleAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  s->add_attribute<double>("test", 123.12);
  EXPECT_EQ(s->get_attribute<double>("test"), 123.12);
}

TEST(Span, StringAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  s->add_attribute<std::string>("test", "test value");
  EXPECT_EQ(s->get_attribute<std::string>("test"), "test value");
}

TEST(Span, BooleanAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  s->add_attribute<bool>("test", true);
  EXPECT_EQ(s->get_attribute<bool>("test"), true);
}

TEST(Span, IntAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  s->add_attribute<int64_t>("test", 12341234);
  EXPECT_EQ(s->get_attribute<int64_t>("test"), 12341234);
}

TEST(Span, OverwritingAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  s->add_attribute<std::string>("test", "test value");
  s->add_attribute<int64_t>("test", 12341234);
  EXPECT_EQ(s->get_attribute<int64_t>("test"), 12341234);
}

TEST(Span, MismatchedTypeAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  s->add_attribute<int64_t>("test", 12341234);
  ASSERT_THROW(s->get_attribute<bool>("test"), std::bad_variant_access);
}

TEST(Span, MissingAttributes){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  ASSERT_THROW(s->get_attribute<bool>("test"), std::out_of_range);
}

TEST(Span, Parenting){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  auto child = new Span("child", t, s->get_context());
  ASSERT_EQ(s->get_context(), child->get_parent_context());
}

TEST(Span, End){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  ASSERT_FALSE(s->is_ended());
  s->end();
  ASSERT_TRUE(s->is_ended());
}

TEST(Span, SpecifiedEnd){
  auto t = new Tracer();
  auto s = new Span("test name", t);
  ASSERT_FALSE(s->is_ended());
  s->end(std::chrono::milliseconds(123));
  ASSERT_EQ(s->get_end_time(), std::chrono::milliseconds(123));
  ASSERT_TRUE(s->is_ended());
}

TEST(Span, DurationTest){
  auto t = new Tracer();
  auto s = new Span("test name", t);

  // waste some time
  auto start = std::chrono::system_clock::now();
  auto diff = std::chrono::system_clock::now() - start;
  while (diff < std::chrono::milliseconds(10)) {
    diff = std::chrono::system_clock::now() - start;
  }

  s->end();
  ASSERT_TRUE(s->get_duration() >= std::chrono::milliseconds(10));
}
