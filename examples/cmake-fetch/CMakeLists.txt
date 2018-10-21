cmake_minimum_required(VERSION 3.11)
project(example)

include(FetchContent)

FetchContent_Declare(termcolor
  GIT_REPOSITORY git://github.com/ikalnytskyi/termcolor.git
  GIT_TAG origin/master)
FetchContent_GetProperties(termcolor)

if(NOT termcolor_POPULATED)
  FetchContent_Populate(termcolor)
  add_subdirectory(${termcolor_SOURCE_DIR} ${termcolor_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(${CMAKE_PROJECT_NAME} example.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE termcolor)
