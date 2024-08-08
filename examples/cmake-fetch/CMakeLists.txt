cmake_minimum_required(VERSION 3.14)
project(example)

include(FetchContent)

FetchContent_Declare(termcolor
  GIT_REPOSITORY https://github.com/ikalnytskyi/termcolor.git
  GIT_TAG origin/master)
FetchContent_MakeAvailable(termcolor)

add_executable(${CMAKE_PROJECT_NAME} example.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE termcolor)
