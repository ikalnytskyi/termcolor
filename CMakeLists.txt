cmake_minimum_required(VERSION 2.8)
project(termcolor)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_CXX_FLAGS "-Werror -Wall -pedantic")
endif()

include_directories(${termcolor_SOURCE_DIR}/include)
add_executable(test_${CMAKE_PROJECT_NAME} test/test.cpp)
add_custom_target(run COMMAND test_${CMAKE_PROJECT_NAME})
