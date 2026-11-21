cmake_minimum_required(VERSION 3.6)
project(example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TERMCOLOR REQUIRED IMPORTED_TARGET termcolor)

add_executable(${CMAKE_PROJECT_NAME} example.cpp)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE PkgConfig::TERMCOLOR)
