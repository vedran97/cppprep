cmake_minimum_required(VERSION 3.14)
project(cppprep)

#
# GoogleTest Setup
# ref: https://google.github.io/googletest/quickstart-cmake.html
#

# GoogleTest requires at least C++14
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

add_compile_options(-Wall -Wpedantic -fsanitize=undefined,address -std=c++23 -O3)
add_link_options(-fsanitize=undefined,address)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Enable compile_commands.json
execute_process(COMMAND cmake -E create_symlink
                "${PROJECT_BINARY_DIR}/compile_commands.json"
                "${PROJECT_SOURCE_DIR}/compile_commands.json")

# declares a dependency on GoogleTest which is downloaded from GitHub
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enables testing for this directory and below
enable_testing()
include(GoogleTest)


#
# c++ Boilerplate Modification Starts Here
# ref: https://iamsorush.com/posts/cpp-cmake-essential/
# ref: https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#


include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(ringbuflib ${PROJECT_SOURCE_DIR}/src/ringbuffer.cpp)
add_library(pidlib ${PROJECT_SOURCE_DIR}/src/pid.cpp)
add_library(fsmlib ${PROJECT_SOURCE_DIR}/src/fsm.cpp)
target_include_directories(ringbuflib PUBLIC
  # list of directories:
  ${CMAKE_SOURCE_DIR}/include
  )
  target_include_directories(pidlib PUBLIC
  # list of directories:
  ${CMAKE_SOURCE_DIR}/include
  )
  target_include_directories(fsmlib PUBLIC
  # list of directories:
  ${CMAKE_SOURCE_DIR}/include
  )

add_subdirectory(tests)

