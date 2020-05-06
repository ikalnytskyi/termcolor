cmake_minimum_required(VERSION 3.0)
project(example)

include(ExternalProject)

ExternalProject_Add(termcolor_project
  GIT_REPOSITORY git://github.com/ikalnytskyi/termcolor.git
  GIT_TAG origin/master

  # Termcolor is a header-only library which means we need to
  # neither configure nor build nor install it. Thus, noop
  # the hooks.
  CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_COMMAND "")
ExternalProject_Get_Property(termcolor_project SOURCE_DIR)

set(CMAKE_CXX_STANDARD 11)

include_directories(${SOURCE_DIR}/include)
add_library(termcolor INTERFACE IMPORTED)
add_dependencies(termcolor termcolor_project)

add_executable(${CMAKE_PROJECT_NAME} example.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE termcolor)
