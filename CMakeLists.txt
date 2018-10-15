cmake_minimum_required(VERSION 3.0)
project(termcolor)

# define target to install and link tests against
add_library(${CMAKE_PROJECT_NAME} INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# ALIAS same as in configure file
# the ALIAS can be used to create examples which use the same syntax as a client
# application, which uses `find_package(libdivide CONFIG)`
# create the alias libdivide::libdivide
add_library(${CMAKE_PROJECT_NAME}::${CMAKE_PROJECT_NAME} ALIAS ${CMAKE_PROJECT_NAME})

option(ENABLE_TESTING "enable testing with CTEST" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_executable(test_${CMAKE_PROJECT_NAME} test/test.cpp)
  # add compiler flags for test target only for GCC and Clang
  target_compile_options(test_${CMAKE_PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Werror -Wall -pedantic>>
    )

  add_test(test_${CMAKE_PROJECT_NAME} test_${CMAKE_PROJECT_NAME})
  target_link_libraries(test_${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}::${CMAKE_PROJECT_NAME})
  add_custom_target(run COMMAND test_${CMAKE_PROJECT_NAME})
endif()

# create install target
install(
  TARGETS ${CMAKE_PROJECT_NAME}
  EXPORT ${CMAKE_PROJECT_NAME}-targets
  INCLUDES DESTINATION include # set include path for installed library target
  )
install(
  FILES include/termcolor/termcolor.hpp
  DESTINATION include/termcolor
  )

# Include module for fuctions
# - 'write_basic_package_version_file'
# - 'configure_package_config_file'
include(CMakePackageConfigHelpers)

# generate and install termcolor-config.cmake file
# Configure '<PROJECT-NAME>-config.cmake'
configure_package_config_file(
  "cmake/config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/termcolor-config.cmake"
  INSTALL_DESTINATION "lib/cmake/termcolor"
)
# install config file
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/termcolor-config.cmake"
  DESTINATION "lib/cmake/termcolor"
)
# install targets file
install(
  EXPORT "${CMAKE_PROJECT_NAME}-targets"
  NAMESPACE "${CMAKE_PROJECT_NAME}::"
  DESTINATION "lib/cmake/termcolor"
)
