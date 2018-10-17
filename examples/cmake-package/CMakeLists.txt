cmake_minimum_required(VERSION 3.0)
project(example)

find_package(termcolor REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} example.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE termcolor::termcolor)
