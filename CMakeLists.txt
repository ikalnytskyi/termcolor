cmake_minimum_required(VERSION 3.0)
project(termcolor)

#
# target
#

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

#
# tests
#

option(TERMCOLOR_TESTS "Build termcolor tests." OFF)

if(TERMCOLOR_TESTS)
  add_executable(test_${PROJECT_NAME} test/test.cpp)
  target_link_libraries(
    test_${PROJECT_NAME} ${PROJECT_NAME}::${PROJECT_NAME})
endif()

#
# install
#

include(CMakePackageConfigHelpers)

configure_package_config_file(
  cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}-config.cmake
  DESTINATION lib/cmake/${PROJECT_NAME})

install(
  DIRECTORY include/
  DESTINATION include)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
  INCLUDES DESTINATION include)

install(
  EXPORT ${PROJECT_NAME}-targets
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME})
