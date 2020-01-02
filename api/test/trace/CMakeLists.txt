include(GoogleTest)

add_executable(span-context_unittest span-context_unittest.cc)
target_link_libraries(span-context_unittest ${GTEST_BOTH_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT} opentelemetry_api)
gtest_add_tests(TARGET span-context_unittest
                TEST_PREFIX trace. 
                TEST_LIST span-context_unittest)

add_executable(span_unittest span_unittest.cc)
target_link_libraries(span_unittest ${GTEST_BOTH_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT} opentelemetry_api)
gtest_add_tests(TARGET span_unittest
                TEST_PREFIX trace. 
                TEST_LIST span_unittest)

add_executable(tracer_unittest tracer_unittest.cc)
target_link_libraries(tracer_unittest ${GTEST_BOTH_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT} opentelemetry_api)
gtest_add_tests(TARGET tracer_unittest
                TEST_PREFIX trace. 
                TEST_LIST tracer_unittest)
