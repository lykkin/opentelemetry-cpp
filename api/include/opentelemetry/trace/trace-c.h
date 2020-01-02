#ifndef INCLUDE_OPEN_TELEMETRY_TRACE_TRACE_C_H_
#define INCLUDE_OPEN_TELEMETRY_TRACE_TRACE_C_H_
#ifdef __cplusplus
#include "./span-context.h"
#include "./span.h"
#include "./tracer.h"
extern "C" {
#endif
struct Tracer;
typedef struct Tracer Tracer;

struct Span;
typedef struct Span Span;

struct SpanContext;
typedef struct SpanContext SpanContext;

//  TRACER METHODS
Tracer* tracer_create();
void tracer_destroy(Tracer* const);
Span* tracer_get_current_span(const Tracer* const);
void tracer_set_current_span(Tracer* const, Span*);
Span* tracer_start_span(Tracer* const, const char*);
void tracer_on_span_end(Tracer* const, const Span* const);

//  SPAN METHODS
Span* span_create(const char*, Tracer* const, const SpanContext* const);
void span_end(Span*);

//  SPAN CONTEXT METHODS
//  SpanContext* span_context_create();
//  const int* const span_context_get_trace_id(const SpanContext* const);
//  const int* const span_context_get_span_id(const SpanContext* const);
#ifdef __cplusplus
}
#endif
#endif  // INCLUDE_OPEN_TELEMETRY_TRACE_TRACE_C_H_
