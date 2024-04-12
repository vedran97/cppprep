# Any C++ source files needed to build this target (cpp-test).
add_executable(prep_tests
  # list of source cpp files:
  main.cpp
  ringbuf_test.cpp
  pid_test.cpp
  fsm_test.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(prep_tests PUBLIC
  # list of include directories:
  ${CMAKE_SOURCE_DIR}/include
  )

# Any dependent libraires needed to build this target.
target_link_libraries(prep_tests PUBLIC
  # list of libraries:
  gtest
  ringbuflib
  pidlib
  fsmlib
  )

# Enable CMake’s test runner to discover the tests included in the
# binary, using the GoogleTest CMake module.
gtest_discover_tests(prep_tests)