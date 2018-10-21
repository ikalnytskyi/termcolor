cmake_minimum_required(VERSION 3.0)
project(example)

add_subdirectory(../.. ${CMAKE_CURRENT_BINARY_DIR}/termcolor EXCLUDE_FROM_ALL)

add_executable(${CMAKE_PROJECT_NAME} example.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE termcolor::termcolor)
